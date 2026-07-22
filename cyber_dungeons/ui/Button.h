#pragma once

#include <raylib.h>

struct Button
{
	Rectangle rect;
	Rectangle textRect;
	Color buttonColor;
	Color textColor;
	int padding;
	const char* text;
	int fontSize;

    enum class ButtonState {
		DEFAULT,
		HOVERED,
		PRESSED
    };

	Action action;

	struct ButtonStyle {
		Color backgroundDefault = GRAY;
		Color backgroundHovered = BLUE;
		Color backgroundPressed = DARKBLUE;

		Color textDefault = BLACK;
		Color textHovered = WHITE;
		Color textPressed = WHITE;
	} style;



	Color currentStyle;
	ButtonState currentState;

	Button(int x, int y, int width, int height, Color buttonColor, const char* text, Color textColor, float fontSize, int padding, Action action) :
		rect(x, y, width, height),
		buttonColor(buttonColor),
		text(text), 
		textColor(textColor),
		fontSize(fontSize),
		padding(padding),
		action(action)
	{
		Vector2 textSize = MeasureTextEx(GetFontDefault(), text, fontSize, fontSize * 0.1f);
		Font defaultFont = GetFontDefault();
		Vector2 centeredTextPosition = centerElement(rect.x, rect.y, rect.width, rect.height, textSize.x, textSize.y);
		textRect.x = centeredTextPosition.x;
		textRect.y = centeredTextPosition.y;
		textRect.width = textSize.x;
		textRect.height = textSize.y;
	}

	Vector2 centerElement(float containerX, float containerY, float containerWidth, float containerHeight, float elementX, float elementY)
	{
		return {
			((containerX + (containerWidth) / 2)) - (elementX / 2),
			((containerY + (containerHeight) / 2)) - (elementY / 2),
		};
	}

	Rectangle getRect() const
	{
		return rect;
	}

	Rectangle getTextRect() const
	{
		return textRect;
	}

	void setButtonColor(Color color)
	{
		buttonColor = color;
	}

	Color getButtonColor() const
	{
		switch (currentState)
		{
		case ButtonState::DEFAULT: return style.backgroundDefault;
		case ButtonState::HOVERED: return style.backgroundHovered;
		case ButtonState::PRESSED: return style.backgroundPressed;
		default: return style.backgroundDefault;
		}
	}

	void setTextColor(Color color)
	{
		textColor = color;
	}

	Color getTextColor() const
	{
		switch (currentState)
		{
		case ButtonState::DEFAULT: return style.textDefault;
		case ButtonState::HOVERED: return style.textHovered;
		case ButtonState::PRESSED: return style.textPressed;
		default: return style.textDefault;
		}
	}

	void setState(ButtonState value)
	{
		currentState = value;
		
		switch (value)
		{
			case ButtonState::DEFAULT:
				currentStyle = style.backgroundDefault;
				break;
			case ButtonState::HOVERED:
				currentStyle = style.backgroundHovered;
				break;
			case ButtonState::PRESSED:
				currentStyle = style.backgroundPressed;
				break;
			default:
				currentStyle = style.backgroundDefault;
				break;
		}
	}

	ButtonState getState() const
	{
		return currentState;
	}

	void setStyle(ButtonStyle value)
	{
		style = value;
	}

	ButtonStyle getStyle() const
	{
		return style;
	}

	const char* getText() const
	{
		return text;
	}

	Action getAction() const
	{
		return action;
	}

	void render() const
	{
		DrawRectangle(getRect().x, getRect().y, getRect().width, getRect().height, getButtonColor());
		DrawText(getText(), getTextRect().x, getTextRect().y, 20, getTextColor());
	}
};