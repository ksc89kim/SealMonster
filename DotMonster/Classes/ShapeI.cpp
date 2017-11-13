//
//  ShapeI.cpp
//  ShapeMaster
//
//  Created by 김선철 on 2014. 3. 1..
//
//

#include "ShapeI.h"
#include "ShapeContainer.h"

ShapeI* ShapeI::create()
{
    ShapeI *pSprite = new ShapeI();
    if (pSprite && pSprite->init())
    {
        pSprite->setValue();
        pSprite->setImage();
        pSprite->autorelease();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}
ShapeObject *ShapeI::getStatusObject(int index)
{
    return nullptr;
}
void ShapeI::setLegend()
{
    
}
void ShapeI::setImage()
{
    
}

void ShapeI::setValue()
{
    
}
void ShapeI::setStatus()
{
    
}
void ShapeI::changeImage()
{
    
}
void ShapeI::setName()
{
    
}
void ShapeI::changeRandShape(int minRandLevel, int maxRandLeve)
{
    ShapeName *firstName = ShapeNameContainer::getInstance()->getRandShapeName(shapeType::kShapeW, minRandLevel, maxRandLeve);
    ShapeName *midName = ShapeNameContainer::getInstance()->getRandShapeName(shapeType::kShapeW, minRandLevel, maxRandLeve);
    ShapeName *lastName = ShapeNameContainer::getInstance()->getRandShapeName(shapeType::kShapeW, minRandLevel, maxRandLeve);
    setNameAndClassNumber(firstName,midName,lastName);
    setStatus();
    changeImage();
    
}
void ShapeI::changeFindShape(int firstIndex,int midIndex, int lastIndex)
{
    ShapeName *firstName = ShapeNameContainer::getInstance()->getFindShapeName(shapeType::kShapeW, firstIndex);
    ShapeName *midName = ShapeNameContainer::getInstance()->getFindShapeName(shapeType::kShapeW, midIndex);
    ShapeName *lastName = ShapeNameContainer::getInstance()->getFindShapeName(shapeType::kShapeW,lastIndex);
    setNameAndClassNumber(firstName,midName,lastName);
    
    setStatus();
    changeImage();
}



