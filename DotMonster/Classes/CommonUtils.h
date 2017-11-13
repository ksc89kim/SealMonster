//
//  CommonUtils.h
//  dotMonster
//
//  Created by 김선철 on 2014. 12. 6..
//
//

#ifndef __dotMonster__CommonUtils__
#define __dotMonster__CommonUtils__

#include "CocosHeader.h"


class CommonUtils:public Ref{
    enum
    {
        kLabel=992929,
        kSelectImage,
    };
private:
    CommonUtils() {};
    ~CommonUtils() {};
    CommonUtils(const CommonUtils &);
    CommonUtils & operator=(const CommonUtils &);
public:
    static CommonUtils &getInstance()
    {
        static CommonUtils _instance;
        return _instance;
    }
    
    //문자열 나누기
    std::vector<std::string> splits(std::string str, std::string delimiter);
    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
    std::vector<std::string> split(const std::string &s, char delim);
    
    void removeDirWithCopy(int &ret,std::string removeFile, std::string file, std::string copyFile);
    void copyFile(const char *srcPath, const char *destPath);
    
    static MenuItem *createMenuItem(const std::string &buttonImage, const ccMenuCallback &callback);
    static MenuItem *createMenuItemLabel(const std::string &content, const ccMenuCallback &callback);
    static MenuItem *createMenuItemLabel(const std::string &content, const Size &size, const ccMenuCallback &callback);
    static void menuItemSpriteAddChild(MenuItemSprite *item, Node *normalNode, Node *selectNode);
    static void setMenuItemLabel(MenuItemSprite *item, const std::string &content);

    static Sprite *createLabelBorder(const std::string &content);
    static Sprite *createLabelBorder(const std::string &content, const Size &size);
    static void setLabelBorderContent(Sprite *labelBorder,const std::string &content);
    static void setLabelBorderAncorPoint(Sprite *labelBorder, const Vec2 &position);
    static void setLabelBorderPoint(Sprite *labelBorder, const Vec2 &position);

    static const Vec2 &changePosition(const Vec2 &position);
    static void fitNode(Node *sprite, float size);
    static void fitNode(Node *sprite, const Size &size);

    static void setLabelAutoSize(Label *label, float baseFontSize, const Size &size);
    static void setFontSize(Label *label,float fontSize);
    static void setFontName(Label *label,const char*fontName);
    static int getFontSize(Label *label);
    
    static const char *getFontName();


};

#endif /* defined(__dotMonster__CommonUtils__) */
