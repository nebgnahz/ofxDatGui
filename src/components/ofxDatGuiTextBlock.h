/*
    Copyright (C) 2015 Stephen Braitsch [http://braitsch.io]

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#pragma once
#include "ofxDatGuiComponent.h"
#include "ofxParagraph.h"

class ofxDatGuiTextBlock : public ofxDatGuiComponent {

    public:

        ofxDatGuiTextBlock(string text = "") : ofxDatGuiComponent("")
        {
            mParagraph.setText(text);
            mParagraph.setIndent(0);
            setTheme(ofxDatGuiComponent::theme.get());
            mStyle.stripe.visible = false;
        }

        void setTheme(ofxDatGuiTheme* theme)
        {
            setComponentStyle(theme);
            ofxDatGuiComponent::setWidth(theme->layout.width, theme->layout.labelWidth);

            mParagraph.setFont(theme->font.ptr);
            mLineHeight = theme->font.ptr->height("A");
            mParagraph.setLeading(mLineHeight / 4);

            mParagraph.setColor(theme->color.label);
        }

        void setWidth(int width, float labelWidth)
        {
            ofxDatGuiComponent::setWidth(width, labelWidth);
            mParagraph.setWidth(width - 6 * mStyle.padding);

            mStyle.height = mParagraph.getHeight() + mLineHeight + 6 * mStyle.padding;
        }

        void setPosition(int x, int y)
        {
            ofxDatGuiComponent::setPosition(x, y);
            mTextRect.x = x;
            mTextRect.y = y;
        }

        void setText(string text)
        {
            mParagraph.setText(text);
        }

        void draw()
        {
            if (!mVisible) return;

            ofPushStyle();
                ofxDatGuiComponent::draw();
                mParagraph.draw(mTextRect.x + 3 * mStyle.padding,
                                mTextRect.y + mLineHeight + 4 * mStyle.padding);
            ofPopStyle();
        }

    protected:
        ofxParagraph mParagraph;
        ofRectangle mTextRect;
        unsigned int mLineHeight;
};
