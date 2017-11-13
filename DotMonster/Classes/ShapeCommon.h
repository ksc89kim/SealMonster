//
//  ShapeCommon.h
//  ShapeMaster
//
//  Created by 김선철 on 2014. 3. 2..
//
//

#ifndef __ShapeMaster__ShapeCommon__
#define __ShapeMaster__ShapeCommon__

#include "Define.h"
#include "ShapeObject.h"
#include "ShapeSkill.h"
#include <queue>
#include "TextDb.h"

class ShapeCommon:public Sprite
{
   
private:
public:
    enum
    {
        kDebuf=999
    };
    LayerColor *_bgColor; //사이즈 테스트
    bool _isSizeTest; //사이즈 테스트
    std::queue<ShapeSkill *> _skillQueue; //스킬
    ShapeObject *_shapeData; //몬스터 데이터
    Sprite *_imageMid; //중간 이미지
    Sprite *_imageTop; //가장 위에 있는 이미지
    
    ShapeCommon();
    ~ShapeCommon();

    bool expUp(float exp); //경험치 업
    float getMaxExp(); //최대 경험치
    void logStatus(); //몬스터 정보 로그
    void setClassScale(); //몬스터 진화 여부에 따른 이미지 스케일
    void checkEvolution(); //몬스터 진화
    void setLegend(bool isLegend); //전설 설정
    void setLegendValue(bool isLegend); //전설값 설정
    bool getLegendValue(); //전설값 여부

    virtual void setName() = 0; //몬스터 이름 설정
    virtual void setStatus() = 0; //몬스터 스탯 설정
    virtual void changeImage() = 0; //이미지 변환
    virtual void changeRandShape(int minRandLevel,int maxRandLeve) = 0; //몬스터 등급 설정 (랜덤)
    virtual void changeFindShape(int firstIndex,int midIndex, int lastIndex) = 0; //몬스터 등급 설정 ()
    virtual ShapeObject *getStatusObject(int index) = 0;
    
    void setFlippedXShape(bool isFlipped); //이미지 반대로..
    void setNameAndClassNumber(ShapeName *firstName, ShapeName *midName, ShapeName *lastName); //이름과 클래스 설정.
    bool isLegend(); //전설 상태
    void damageAnimation(float delayTime = 0.0f); //데미지 애니메이션
    void debufAnimation(float delayTime = 0.0f); //진행중인 디버프 애니메이션
    void startDebufAnimation(); //시작 디버프 애니메이션
    void stopDebufAnimation(); //끝 디버프 애니메이션
    void stopAnimation(); //스탑 애니메이션
    void missAnimation(); //미스 애니메이션
    void catchFailAnimation(); //캐치 애니메이션
 
    void removeAnimation(Node *target); //애니메이션 삭제
    static ShapeCommon *copyShapeCommonImage(ShapeCommon *copyObject); //몬스터 카피
    static ShapeCommon *copyShapeCommon(ShapeCommon *copyObject); //몬스터 카피

    void setOpacityShape(GLubyte opacity); //opcity
    void setColorShape(const Color3B& color); //color
    Size getVisibleContentSize(); //사이즈
    float getClassAll(); //등급 평균
    const char* getClassAllName(); //등급 평균 이름
    const char *getFullName(); //몬스터 풀 이름
    void setSizeTest(bool isSizeTest); //사이즈 테스트 여부
};

#endif /* defined(__ShapeMaster__ShapeCommon__) */
