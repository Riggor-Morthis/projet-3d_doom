#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <geometryengine.h>
#include <transformation.h>
#include <QOpenGLTexture>
#include <vector>
#include "boundingbox.h"

/**
 * @brief Représente un gameobject, celui ci est composé d'un mesh, d'une transformation et d'une texture
 */
class gameobject
{
public :
    ////Constructors
    gameobject();
    gameobject(GeometryEngine * m,transformation t, QOpenGLTexture * texture_) : mesh(m), transform(t),texture(texture_){

    }

    ////Methods
    void setTransform(transformation t){transform = t;}

    //Display methods
    void displayObject(QMatrix4x4 parentTransform, QOpenGLShaderProgram *program,QMatrix4x4 projection);
    void displayObject(QOpenGLShaderProgram *program,QMatrix4x4 projection);
    void displayAll(QMatrix4x4 parentTransform, QOpenGLShaderProgram *program,QMatrix4x4 projection);
    void displayAll(QOpenGLShaderProgram *program,QMatrix4x4 projection);
    void addChild(gameobject * g){childs.push_back(g);}
    std::vector<gameobject *> getChilds(){return childs;}


    //Getters
    std::vector<QVector3D> getActualVertices();
    std::vector<int> getActualIndexs(){return mesh->getIndex();}
    boundingBox getBBox();
    QVector3D getBarycentre();
    transformation getTransform(){ return transformation(transform);}
    triangle getClosestTriangleDown(QVector3D p);
    triangle getClosestTriangleDown(QVector3D p,double & distance);

    //Debug methods
    void displayBaseValue(){
        qInfo() << "Creation"<<endl;
        std::vector<QVector3D> v = mesh->getBaseVertices();
        for(QVector3D ver : v){
            qInfo()<<ver<<endl;
        }
    }




protected:
    ////Variables
    QOpenGLTexture * texture;
    GeometryEngine * mesh;
    bool isDisplaying = true;
    transformation transform;
    std::vector<gameobject *> childs;

};
#endif

