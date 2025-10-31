#include "../include/parser.hpp"

Settings parse_cam_settings(XMLElement *camera){
    XMLElement *p = camera->FirstChildElement("position");
        float px = p->FloatAttribute("x");
        float py = p->FloatAttribute("y");
        float pz = p->FloatAttribute("z");
        Point position = Point(px,py,pz);
    XMLElement *l = camera->FirstChildElement("lookAt");
        float lx = l->FloatAttribute("x");
        float ly = l->FloatAttribute("y");
        float lz = l->FloatAttribute("z");
        Point lookAt = Point(lx,ly,lz);
    XMLElement *u = camera->FirstChildElement("up");
    Point up;
    if (u != NULL){
        float ux = u->IntAttribute("x");
        float uy = u->IntAttribute("y");
        float uz = u->IntAttribute("z");
        up = Point(ux,uy,uz);
    }
    else up = Point(0,1,0);
    XMLElement *pr = camera->FirstChildElement("projection");
    Point projection;
    if (pr != NULL){
        float fov = pr->FloatAttribute("fov");
        float near = pr->FloatAttribute("near");
        float far = pr->FloatAttribute("far");
        projection = Point(fov,near,far);
    }
    else projection = Point(60,1,1000);
    return Settings(position,lookAt,up,projection);
}

Model parseModel(XMLElement *m, string filename){
    XMLElement *pin;
    Model model = Model(filename);
    for (pin = m->FirstChildElement(); pin != NULL; pin = pin->NextSiblingElement()){
        if(!strcmp(pin->Name(),"color")){
            XMLElement *rgb = pin->FirstChildElement("rgb");
            if (rgb != NULL){
                float R = rgb->FloatAttribute("R");
                float G = rgb->FloatAttribute("G");
                float B = rgb->FloatAttribute("B");
                Color _color = Color(Point(R,G,B));
                model.add_color(_color);
            }
            else{
                XMLElement *diffuse = pin->FirstChildElement("diffuse");
                    float dR = diffuse->FloatAttribute("R");
                    float dG = diffuse->FloatAttribute("G");
                    float dB = diffuse->FloatAttribute("B");
                    Point d = Point(dR, dG, dB);
                XMLElement *ambient = pin->FirstChildElement("ambient");
                    float aR = ambient->FloatAttribute("R");
                    float aG = ambient->FloatAttribute("G");
                    float aB = ambient->FloatAttribute("B");
                    Point a = Point(aR,aG,aB);
                XMLElement *specular = pin->FirstChildElement("specular");
                    float sR = specular->FloatAttribute("R");
                    float sG = specular->FloatAttribute("G");
                    float sB = specular->FloatAttribute("B");
                    Point s = Point(sR,sG,sB);
                XMLElement *emissive = pin->FirstChildElement("emissive");
                    float eR = emissive->FloatAttribute("R");
                    float eG = emissive->FloatAttribute("G");
                    float eB = emissive->FloatAttribute("B");
                    Point e = Point(eR,eG,eB);
                XMLElement *shininess = pin->FirstChildElement("shininess");
                    float value = shininess->FloatAttribute("value");
                model.add_color(Color(d,a,s,e, value));
            }
        }
        else if(!strcmp(pin->Name(),"texture")){
            const char * texture = pin->Attribute("file");
            if(texture) {
                std::string tex(texture);
                model.add_texture(tex);
            }
        }
    }
    return model;
}


Group *parseGroup(XMLElement *node){
    Group *group = new Group();
    /* <transform>*/
    XMLElement *t = node->FirstChildElement("transform");
    if(t != NULL){
        XMLElement *tr;
        for (tr = t->FirstChildElement(); tr != NULL; tr = tr->NextSiblingElement()){
            float px = tr->FloatAttribute("x", -1);
            float py = tr->FloatAttribute("y");
            float pz = tr->FloatAttribute("z");
            if(!strcmp(tr->Name(),"translate")){
                Translate *translation;
                if (px != -1){
                    translation = new Translate(px,py,pz);
                }
                else{
                    float time = tr->FloatAttribute("time");
                    string align = tr->Attribute("align");
                    int f_align = ((align.compare("true"))==0) ? 1 : 0;
                    vector<Point> _curves;
                    XMLElement *points;
                    for (points = tr->FirstChildElement(); points != NULL; points = points->NextSiblingElement()){
                        float _px = points->FloatAttribute("x");
                        float _py = points->FloatAttribute("y");
                        float _pz = points->FloatAttribute("z");
                        _curves.push_back(Point(_px,_py,_pz));
                    }
                    translation = new Translate(time, f_align, _curves);
                }
                group->add_transformation(translation);
            }
            else if(!strcmp(tr->Name(),"rotate")){
                Rotate *rotation = new Rotate(px,py,pz);
                float angle = tr->IntAttribute("angle", -1);
                float time = tr->FloatAttribute("time", -1);
                if(angle != -1) rotation->add_angle(angle);
                else if (time != -1) rotation->add_time(time);

                group->add_transformation(rotation);
            }
            else if(!strcmp(tr->Name(),"scale")){
                Scale *scale = new Scale(px,py,pz);
                group->add_transformation(scale);
            }
        }
    }
    /* <models>*/
    XMLElement *m = node->FirstChildElement("models");
    if (m != NULL){
        vector<Model> models;
        XMLElement * model;
        for (model = m->FirstChildElement(); model != NULL; model = model->NextSiblingElement()){
            if(!strcmp(model->Name(),"model")){
                string filename = model->Attribute("file");
                Model mm = parseModel(model, filename);
                models.push_back(mm);  
            }
        }
        group->add_models(models);
    }
    /* <group>*/
    XMLElement *gChild = node->FirstChildElement("group");
    for( ; gChild != NULL; gChild = gChild->NextSiblingElement()){
        Group *gc = parseGroup(gChild);
        group->add_group_child(gc);
    }
    return group;
}


vector<Light*> parseLight(XMLElement *node){
    vector<Light*> lights;
    XMLElement * l;
    int counter = 0;
    for (l = node->FirstChildElement(); l != NULL; l = l->NextSiblingElement(), counter++){
        if (!strcmp(l->Attribute("type"),"point")){
            float posX = l->FloatAttribute("posX");
            float posY = l->FloatAttribute("posY");
            float posZ = l->FloatAttribute("posZ");
            Light *p = new Light_point(posX,posY,posZ,counter);
            lights.push_back(p);
        }
        else if (!strcmp(l->Attribute("type"),"directional")){
            float dirX = l->FloatAttribute("dirX");
            float dirY = l->FloatAttribute("dirY");
            float dirZ = l->FloatAttribute("dirZ");
            Light *d = new Light_directional(dirX,dirY,dirZ,counter);
            lights.push_back(d);
        }
        else if (!strcmp(l->Attribute("type"),"spotlight")){
            float posX = l->FloatAttribute("posX");
            float posY = l->FloatAttribute("posY");
            float posZ = l->FloatAttribute("posZ");
            Point pos = Point(posX,posY,posZ);
            float dirX = l->FloatAttribute("dirX");
            float dirY = l->FloatAttribute("dirY");
            float dirZ = l->FloatAttribute("dirZ");
            Point dir = Point(dirX,dirY,dirZ);
            float cutoff = l->FloatAttribute("cutoff");
            Light *s = new Light_spotlight(pos,dir,cutoff,counter);
            lights.push_back(s);
        }
    }
    return lights;
}



XML *parse(string filepath){
    XML *_data = new XML();
    XMLDocument doc;
    int err = doc.LoadFile(filepath.c_str());
    if (err == 0){
        XMLElement *root = doc.RootElement();
        XMLElement *node;
        for(node = root->FirstChildElement();node != NULL;node = node -> NextSiblingElement()){
            if(!strcmp(node->Name(),"window")){
                int width = node->IntAttribute("width");
                int height = node->IntAttribute("height");
                _data->add_window_settings(width,height);
            }
            else if(!strcmp(node->Name(),"camera")){
                Settings _settings = parse_cam_settings(node);
                _data->add_cam_settings(_settings);
            }
            else if(!strcmp(node->Name(),"group")){
                Group *g = parseGroup(node);
                _data->add_group(g);
           }
           else if(!strcmp(node->Name(), "lights")){
                vector<Light*> lights = parseLight(node);
                _data->add_lights(lights);
                
           }
        }
        return _data;

    }
    else{
        doc.PrintError();
        return new XML();
    }
}