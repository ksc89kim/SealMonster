//
//  ShapeZ.cpp
//  ShapeMaster
//
//  Created by 김선철 on 2014. 3. 1..
//
//

#include "ShapeZ.h"
#include "ShapeContainer.h"

ShapeZ* ShapeZ::create()
{
    ShapeZ *pSprite = new ShapeZ();
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
ShapeObject *ShapeZ::getStatusObject(int index)
{
    return nullptr;
}
void ShapeZ::setName()
{
    
}
void ShapeZ::setImage()
{
    
}

void ShapeZ::setValue()
{
    
}
void ShapeZ::setStatus()
{
    
}
void ShapeZ::changeImage()
{
   
}
void ShapeZ::changeRandShape(int minRandLevel, int maxRandLeve)
{
    ShapeName *firstName = ShapeNameContainer::getInstance()->getRandShapeName(shapeType::kShapeZ, minRandLevel, maxRandLeve);
    ShapeName *midName = ShapeNameContainer::getInstance()->getRandShapeName(shapeType::kShapeZ, minRandLevel, maxRandLeve);
    ShapeName *lastName = ShapeNameContainer::getInstance()->getRandShapeName(shapeType::kShapeZ, minRandLevel, maxRandLeve);
    
    setNameAndClassNumber(firstName,midName,lastName);
    
    setStatus();
    changeImage();
    
}
void ShapeZ::changeFindShape(int firstIndex,int midIndex, int lastIndex)
{
    ShapeName *firstName = ShapeNameContainer::getInstance()->getFindShapeName(shapeType::kShapeZ, firstIndex);
    ShapeName *midName = ShapeNameContainer::getInstance()->getFindShapeName(shapeType::kShapeZ, midIndex);
    ShapeName *lastName = ShapeNameContainer::getInstance()->getFindShapeName(shapeType::kShapeZ,lastIndex);
    
    setNameAndClassNumber(firstName,midName,lastName);

    
    setStatus();
    changeImage();
}
