//
//  CommonUtils.cpp
//  dotMonster
//
//  Created by 김선철 on 2014. 12. 6..
//
//

#include "CommonUtils.h"

class Splitter {
    //! Contains the split tokens
    std::vector<std::string> _tokens;
public:
    //! Subscript type for use with operator[]
    typedef std::vector<std::string>::size_type size_type;
public:
    //! Create and initialize a new Splitter
    //!
    //! \param[in] src The string to split
    //! \param[in] delim The delimiter to split the string around
    Splitter ( const std::string& src, const std::string& delim )
    {
        reset ( src, delim );
    }
    //! Retrieve a split token at the specified index
    //!
    //! \param[in] i The index to search for a token
    //! \return The token at the specified index
    //! \throw std::out_of_range If the index is invalid
    std::string& operator[] ( size_type i )
    {
        return _tokens.at ( i );
    }
    //! Retrieve the number of split tokens
    //!
    //! \return The number of split tokesn
    size_type size() const
    {
        return _tokens.size();
    }
    //! Re-initialize with a new soruce and delimiter
    //!
    //! \param[in] src The string to split
    //! \param[in] delim The delimiter to split the string around
    void reset ( const std::string& src, const std::string& delim )
    {
        std::vector<std::string> tokens;
        std::string::size_type start = 0;
        std::string::size_type end;
        for ( ; ; ) {
            end = src.find ( delim, start );
            tokens.push_back ( src.substr ( start, end - start ) );
            // We just copied the last token
            if ( end == std::string::npos )
                break;
            // Exclude the delimiter in the next search
            start = end + delim.size();
        }
        _tokens.swap ( tokens );
    }
};

std::vector<std::string> CommonUtils::splits(std::string str, std::string delimiter)
{
    std::vector<std::string> arr;
    
    Splitter split ( str, delimiter.c_str() );
    for ( Splitter::size_type i = 0; i < split.size(); i++ )
        arr.push_back(split[i]);
    
    return arr;
}

std::vector<std::string> &CommonUtils::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> CommonUtils::split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    return split(s, delim, elems);
}

void CommonUtils::removeDirWithCopy(int &ret,std::string removeFile, std::string file, std::string copyFile)
{
    if (FileUtils::getInstance()->isFileExist(removeFile.c_str()))
    {
        FileUtils::getInstance()->removeFile(removeFile.c_str());
    }
    this->copyFile(file.c_str(), copyFile.c_str());
}
void CommonUtils::copyFile(const char *srcPath, const char *destPath)
{
    auto data =  FileUtils::getInstance()->getDataFromFile(srcPath);
    FILE* dest = fopen(destPath, "wb");
    fwrite(data.getBytes(), 1, data.getSize(), dest);
    fclose(dest);
}

MenuItem *CommonUtils::createMenuItem(const std::string &buttonImage, const ccMenuCallback &callback)
{
    Sprite *normalImage = Sprite::create(buttonImage);
    Sprite *selectImage = Sprite::create(buttonImage);
    selectImage->setColor(Color3B(150,150,150));
    MenuItemSprite *menu = MenuItemSprite::create(normalImage, selectImage, callback);
    return menu;
}
MenuItem *CommonUtils::createMenuItemLabel(const std::string &content, const ccMenuCallback &callback)
{
    Sprite *normalImage = createLabelBorder(content);
    Sprite *selectImage = createLabelBorder(content);
    Scale9Sprite *clickBorder = Scale9Sprite::create("borderClick.png");
    clickBorder->setContentSize(selectImage->getContentSize());
    clickBorder->setPosition(Vec2(selectImage->getContentSize().width/2, selectImage->getContentSize().height/2));
    selectImage->addChild(clickBorder,kSelectImage,kSelectImage);
    //selectImage->setColor(Color3B(150,150,150));
    MenuItemSprite *menu = MenuItemSprite::create(normalImage, selectImage, callback);
    return menu;
}

MenuItem *CommonUtils::createMenuItemLabel(const std::string &content, const Size &size, const ccMenuCallback &callback)
{
    Sprite *normalImage = createLabelBorder(content,size);
    Sprite *selectImage = createLabelBorder(content,size);
    Scale9Sprite *clickBorder = Scale9Sprite::create("borderClick.png");
    clickBorder->setContentSize(selectImage->getContentSize());
    clickBorder->setPosition(Vec2(selectImage->getContentSize().width/2, selectImage->getContentSize().height/2));
    selectImage->addChild(clickBorder,9999);
    //selectImage->setColor(Color3B(150,150,150));
    MenuItemSprite *menu = MenuItemSprite::create(normalImage, selectImage, callback);
    return menu;
}

void CommonUtils::menuItemSpriteAddChild(MenuItemSprite *item, Node *normalNode, Node *selectNode)
{
    item->getNormalImage()->addChild(normalNode);
    item->getSelectedImage()->addChild(selectNode);
}
void CommonUtils::setMenuItemLabel(MenuItemSprite *item, const std::string &content)
{
    setLabelBorderContent((Sprite *)item->getNormalImage(), content);
    setLabelBorderContent((Sprite *)item->getSelectedImage(), content);
    Sprite *clickBorder = (Sprite *)item->getSelectedImage()->getChildByTag(kSelectImage);
    if(clickBorder)
    {
        clickBorder->setContentSize(item->getSelectedImage()->getContentSize());
        clickBorder->setPosition(Vec2(item->getSelectedImage()->getContentSize().width/2, item->getSelectedImage()->getContentSize().height/2));
    }
}


Sprite *CommonUtils::createLabelBorder(const std::string &content)
{
    Scale9Sprite *sprite = Scale9Sprite::create("border.png");
    Label *label = Label::createWithTTF(content,CommonUtils::getFontName(),FONT_SIZE);
    label->setColor(Color3B::BLACK);
    sprite->setContentSize(Size(label->getContentSize().width+FONT_SIZE,label->getContentSize().height+FONT_SIZE));
    label->setPosition(Vec2(sprite->getContentSize().width/2, sprite->getContentSize().height/2));
    label->setTag(kLabel);
    sprite->addChild(label);
    return (Sprite *)sprite;
}
Sprite *CommonUtils::createLabelBorder(const std::string &content, const Size &size)
{
    Scale9Sprite *sprite = Scale9Sprite::create("border.png");
    Label *label = Label::createWithTTF(content,CommonUtils::getFontName(),FONT_SIZE);
    label->setColor(Color3B::BLACK);
    label->setTag(kLabel);
    float width = (size.width>label->getContentSize().width+FONT_SIZE)?size.width:label->getContentSize().width+FONT_SIZE;
    float height = (size.height>label->getContentSize().height+FONT_SIZE)?size.height:label->getContentSize().height+FONT_SIZE;
    sprite->setContentSize(Size(width,height));
    label->setPosition(Vec2(sprite->getContentSize().width/2, sprite->getContentSize().height/2));
    sprite->addChild(label);
    return (Sprite *)sprite;
}
void CommonUtils::setLabelBorderContent(Sprite *labelBorder,const std::string &content)
{
    Label *label = (Label *)labelBorder->getChildByTag(kLabel);
    if(label)
    {
        label->setString(content);
        labelBorder->setContentSize(Size(label->getContentSize().width+FONT_SIZE,label->getContentSize().height+FONT_SIZE));
    }
}
void CommonUtils::setLabelBorderAncorPoint(Sprite *labelBorder, const Vec2 &position)
{
    Label *label = (Label *)labelBorder->getChildByTag(kLabel);
    if(label)
    {
        label->setAnchorPoint(position);
    }
}
void CommonUtils::setLabelBorderPoint(Sprite *labelBorder, const Vec2 &position)
{
    Label *label = (Label *)labelBorder->getChildByTag(kLabel);
    if(label)
    {
        label->setPosition(position);
    }
}
const Vec2 &CommonUtils::changePosition(const Vec2 &position)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float changePositionY = (position.y/640.0f)*100;
    changePositionY = visibleSize.height*changePositionY/100;
    
    float changePositionX = (position.x/960.0f)*100;
    changePositionX = visibleSize.width*changePositionX/100;

     Vec2 newPosition = Vec2(changePositionX,changePositionY);
    log("new Position X %f", newPosition.x);
    log("new Position y %f", newPosition.y);
    return newPosition;
}

void CommonUtils::fitNode(Node *sprite, float size)
{
    float scaleX = size / sprite->getContentSize().width;
    float scaleY = size / sprite->getContentSize().height;
    sprite->setScaleX(scaleX);
    sprite->setScaleY(scaleY);
}
void CommonUtils::fitNode(Node *sprite, const Size &size)
{
    float scaleX = size.width / sprite->getContentSize().width;
    float scaleY = size.height / sprite->getContentSize().height;
    sprite->setScaleX(scaleX);
    sprite->setScaleY(scaleY);
}

void CommonUtils::setLabelAutoSize(Label *label, float baseFontSize, const Size &size)
{
    float minSize = 9;
    Size labelSize = label->getContentSize();
    setFontSize(label,baseFontSize);
    for(int i=0;i<5;i++)
    {
        if(!(label->getContentSize().width > size.width && getFontSize(label) > minSize))
            break;
        else
            setFontSize(label,getFontSize(label)-1);
    }
    float low = minSize;
    float high = getFontSize(label);
    int count=0;
    if (labelSize.width > size.width && getFontSize(label) > minSize) {
        while(low<=high && getFontSize(label) > minSize)
        {
            count++;
            float mid = (low+high)/2;
            
            setFontSize(label,mid);
            labelSize = label->getContentSize();
            if(size.width-getFontSize(label)<labelSize.width && labelSize.width < size.width)
                break;
            else if(labelSize.width>size.width)
                high = mid-1;
            else if(labelSize.width<size.width)
                low = mid+1;
            else
                break;
        }
    }
    while (label->getContentSize().height > size.height && getFontSize(label) > minSize) {
        setFontSize(label,getFontSize(label)-1);
    }
}
void CommonUtils::setFontSize(Label *label,float fontSize)
{
    TTFConfig labelTTF = label->getTTFConfig();
    TTFConfig changeTTF(labelTTF.fontFilePath.c_str(),fontSize,labelTTF.glyphs);
    label->setTTFConfig(changeTTF);
}

void CommonUtils::setFontName(Label *label,const char*fontName)
{
    TTFConfig labelTTF = label->getTTFConfig();
    TTFConfig changeTTF(fontName,labelTTF.fontSize,labelTTF.glyphs);
    label->setTTFConfig(changeTTF);
}
int CommonUtils::getFontSize(Label *label)
{
    TTFConfig labelTTF = label->getTTFConfig();
    return labelTTF.fontSize;
}
const char *CommonUtils::getFontName()
{
    LanguageType ltype = Application::getInstance()->getCurrentLanguage();
    switch (ltype) {
        case LanguageType::KOREAN:
            return "fonts/NanumGothic.ttf";
                        break;
        case LanguageType::CHINESE:
            return "fonts/c.ttf";
                        break;
        default:
            return "fonts/c.ttf";
            break;
    }
}

