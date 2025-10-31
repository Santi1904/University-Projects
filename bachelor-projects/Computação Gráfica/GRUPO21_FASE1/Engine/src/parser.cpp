#include "../include/parser.hpp"

Settings parse(string filepath){
    XMLDocument doc;
    int err = doc.LoadFile(filepath.c_str());
    if (err == 0){
        XMLElement *root = doc.RootElement();
        XMLElement *cwindow = root->FirstChildElement("window");
            int width = cwindow->IntAttribute("width");
            int height = cwindow->IntAttribute("height");
        XMLElement *ccamera = root->FirstChildElement("camera");
            XMLElement *ccposition = ccamera->FirstChildElement("position");
                float px = ccposition->FloatAttribute("x");
                float py = ccposition->FloatAttribute("y");
                float pz = ccposition->FloatAttribute("z");
                Point position = Point(px,py,pz);
            XMLElement *cclookAt = ccamera->FirstChildElement("lookAt");
                float lx = cclookAt->FloatAttribute("x");
                float ly = cclookAt->FloatAttribute("y");
                float lz = cclookAt->FloatAttribute("z");
                Point lookAt = Point(lx,ly,lz);
            XMLElement *ccup = ccamera->FirstChildElement("up");
                float ux = ccup->IntAttribute("x");
                float uy = ccup->IntAttribute("y");
                float uz = ccup->IntAttribute("z");
                Point up = Point(ux,uy,uz);
            XMLElement *ccprojection = ccamera->FirstChildElement("projection");
                float fov = ccprojection->FloatAttribute("fov");
                float near = ccprojection->FloatAttribute("near");
                float far = ccprojection->FloatAttribute("far");
                Point projection = Point(fov,near,far);
        XMLElement *cgroup = root->FirstChildElement("group");
            XMLElement *ccmodels = cgroup->FirstChildElement("models");
                vector<string> models;
                XMLElement * cccmodel;
                for (cccmodel = ccmodels->FirstChildElement(); cccmodel; cccmodel = cccmodel->NextSiblingElement()){
                    models.push_back(cccmodel->Attribute("file"));
                }
        return Settings(width,height,position,lookAt,up,projection,models);
        
    }
    else{
        doc.PrintError();
        return Settings();
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