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


Group *parseGroup(XMLElement *node){
    Group *group = new Group();
    /* <transform>*/
    XMLElement *t = node->FirstChildElement("transform");
    if(t != NULL){
        XMLElement *tr;
        for (tr = t->FirstChildElement(); tr != NULL; tr = tr->NextSiblingElement()){
            float px = tr->FloatAttribute("x");
            float py = tr->FloatAttribute("y");
            float pz = tr->FloatAttribute("z");
            if(!strcmp(tr->Name(),"translate")){
                Translate *translation = new Translate(px,py,pz);
                group->add_transformation(translation);
            }
            else if(!strcmp(tr->Name(),"rotate")){
                float angle = tr->IntAttribute("angle");
                Rotate *rotation = new Rotate(angle,px,py,pz);
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
        XMLElement * model;  
        vector<string> models;          
        for (model = m->FirstChildElement(); model != NULL; model = model->NextSiblingElement()){
            if(!strcmp(model->Name(),"model")){
                models.push_back(model->Attribute("file"));
            }
            else if(!strcmp(model->Name(),"color")){
                XMLElement *rgb = model->FirstChildElement("rgb");
                if (rgb != NULL){
                    float R = rgb->FloatAttribute("R");
                    float G = rgb->FloatAttribute("G");
                    float B = rgb->FloatAttribute("B");
                    Color _color = Color(Point(R,G,B));
                    group->add_color(_color);
                }
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




XML *parse(string filepath){
    XML *data = new XML();
    XMLDocument doc;
    int err = doc.LoadFile(filepath.c_str());
    if (err == 0){
        XMLElement *root = doc.RootElement();
        XMLElement *node;
        for(node = root->FirstChildElement();node != NULL;node = node -> NextSiblingElement()){
            if(!strcmp(node->Name(),"window")){
                int width = node->IntAttribute("width");
                int height = node->IntAttribute("height");
                data->add_window_settings(width,height);
            }
            else if(!strcmp(node->Name(),"camera")){
                Settings _settings = parse_cam_settings(node);
                data->add_cam_settings(_settings);
            }
            else if(!strcmp(node->Name(),"group")){
                Group *g = parseGroup(node);
                data->add_group(g);
           }
        }
        return data;

    }
    else{
        doc.PrintError();
        return new XML();
    }
}




vector<Point> parse3D_file(string filepath){
    vector<Point> points;
    string model = "../models/" + filepath;
    ifstream file(model);
    string line;
    getline(file,line);
    istringstream ssline(line);
    int numPoints;
    ssline >> numPoints;
    float x,y,z;
    for(int i = 0; i < numPoints; i++){
        getline(file,line);
		istringstream ssline(line);
        ssline >> x >> y >> z;
        Point p = Point(x,y,z);
        p.coords();
		points.push_back(p);
    }
    return points;
}