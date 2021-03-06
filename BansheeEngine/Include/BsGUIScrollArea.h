//__________________________ Banshee Project - A modern game development toolkit _________________________________//
//_____________________________________ www.banshee-project.com __________________________________________________//
//________________________ Copyright (c) 2014 Marko Pintera. All rights reserved. ________________________________//
#pragma once

#include "BsPrerequisites.h"
#include "BsGUIElementContainer.h"

namespace BansheeEngine
{
	/**
	 * @brief	Scroll bar options for a GUI scroll area.
	 */
	enum class ScrollBarType
	{
		ShowIfDoesntFit,
		AlwaysShow,
		NeverShow
	};

	/**
	 * @brief	A GUI element container with support for vertical & horizontal scrolling.
	 */
	class BS_EXPORT GUIScrollArea : public GUIElementContainer
	{
	public:
		/**
		 * Returns type name of the GUI element used for finding GUI element styles. 
		 */
		static const String& getGUITypeName();

		/**
		 * @brief	Creates a new empty scroll area.
		 *
		 * @param	vertBarType		Vertical scrollbar options.
		 * @param	horzBarType		Horizontal scrollbar options.
		 * @param	scrollBarStyle	(Optional) Style used by the scroll bars.
		 * @param	scrollAreaStyle	(Optional) Style used by the scroll content area.
		 */
		static GUIScrollArea* create(ScrollBarType vertBarType, ScrollBarType horzBarType, 
			const String& scrollBarStyle = StringUtil::BLANK, const String& scrollAreaStyle = StringUtil::BLANK);

		/**
		 * @brief	Creates a new empty scroll area.
		 *
		 * @param	vertBarType		Vertical scrollbar options.
		 * @param	horzBarType		Horizontal scrollbar options.
		 * @param	layoutOptions	Options that allows you to control how is the element positioned in
		 *							GUI layout. This will override any similar options set by style.
		 * @param	scrollBarStyle	(Optional) Style used by the scroll bars.
		 * @param	scrollAreaStyle	(Optional) Style used by the scroll content area.
		 */
		static GUIScrollArea* create(ScrollBarType vertBarType, ScrollBarType horzBarType, 
			const GUIOptions& layoutOptions, const String& scrollBarStyle = StringUtil::BLANK, 
			const String& scrollAreaStyle = StringUtil::BLANK);

		/**
		 * @brief	Creates a new empty scroll area. Scroll bars will be show if needed and hidden otherwise.
		 *
		 * @param	scrollBarStyle	(Optional) Style used by the scroll bars.
		 * @param	scrollAreaStyle	(Optional) Style used by the scroll content area.
		 */
		static GUIScrollArea* create(const String& scrollBarStyle = StringUtil::BLANK, 
			const String& scrollAreaStyle = StringUtil::BLANK);

		/**
		 * @brief	Creates a new empty scroll area. Scroll bars will be show if needed and hidden otherwise.
		 *
		 * @param	layoutOptions	Options that allows you to control how is the element positioned in
		 *							GUI layout. This will override any similar options set by style.
		 * @param	scrollBarStyle	(Optional) Style used by the scroll bars.
		 * @param	scrollAreaStyle	(Optional) Style used by the scroll content area.
		 */
		static GUIScrollArea* create(const GUIOptions& layoutOptions, const String& scrollBarStyle = StringUtil::BLANK, 
			const String& scrollAreaStyle = StringUtil::BLANK);

		/**
		 * @copydoc	GUIElementContainer::getElementType
		 */
		virtual ElementType getElementType() const { return ElementType::ScrollArea; }

		/**
		 * @brief	Returns the scroll area layout that you may use to add elements inside the scroll area.
		 */
		GUILayout& getLayout() const { return *mContentLayout; }

		/**
		 * @brief	Scrolls the area up by specified amount of pixels, if possible.
		 */
		void scrollUpPx(UINT32 pixels);

		/**
		 * @brief	Scrolls the area down by specified amount of pixels, if possible.
		 */
		void scrollDownPx(UINT32 pixels);

		/**
		 * @brief	Scrolls the area left by specified amount of pixels, if possible.
		 */
		void scrollLeftPx(UINT32 pixels);

		/**
		 * @brief	Scrolls the area right by specified amount of pixels, if possible.
		 */
		void scrollRightPx(UINT32 pixels);

		/**
		 * @brief	Scrolls the area up by specified percentage (ranging [0, 1]), if possible.
		 */
		void scrollUpPct(float percent);

		/**
		 * @brief	Scrolls the area down by specified percentage (ranging [0, 1]), if possible.
		 */
		void scrollDownPct(float percent);

		/**
		 * @brief	Scrolls the area left by specified percentage (ranging [0, 1]), if possible.
		 */
		void scrollLeftPct(float percent);

		/**
		 * @brief	Scrolls the area right by specified percentage (ranging [0, 1]), if possible.
		 */
		void scrollRightPct(float percent);
	protected:
		~GUIScrollArea();

		/**
		 * @copydoc GUIElementContainer::updateBounds
		 */
		virtual void updateClippedBounds();
	private:
		GUIScrollArea(ScrollBarType vertBarType, ScrollBarType horzBarType, 
			const String& scrollBarStyle, const String& scrollAreaStyle, const GUILayoutOptions& layoutOptions);

		/**
		 * @copydoc	GUIElementContainer::mouseEvent
		 */
		virtual bool mouseEvent(const GUIMouseEvent& ev);

		/**
		 * @brief	Scrolls the contents to the specified position.
		 *			(0 meaning top-most part of the content is visible,
		 *			and 1 meaning bottom-most part is visible)
		 */
		void scrollToVertical(float pct);

		/**
		 * @brief	Scrolls the contents to the specified position.
		 *			(0 meaning left-most part of the content is visible,
		 *			and 1 meaning right-most part is visible)
		 */
		void scrollToHorizontal(float pct);

		/**
		 * @brief	Called when the vertical scrollbar moves. 
		 *
		 * @param	pct	Scrollbar position ranging [0, 1].
		 */
		void vertScrollUpdate(float pct);

		/**
		 * @brief	Called when the horizontal scrollbar moves. 
		 *
		 * @param	pct	Scrollbar position ranging [0, 1].
		 */
		void horzScrollUpdate(float pct);

		/**
		 * @copydoc	GUIElementContainer::_updateLayoutInternal
		 */
		void _updateLayoutInternal(INT32 x, INT32 y, UINT32 width, UINT32 height,
			RectI clipRect, UINT8 widgetDepth, UINT16 areaDepth);

		ScrollBarType mVertBarType;
		ScrollBarType mHorzBarType;
		String mScrollBarStyle;

		GUILayout* mContentLayout;
		GUIScrollBarVert* mVertScroll;
		GUIScrollBarHorz* mHorzScroll;

		float mVertOffset;
		float mHorzOffset;

		UINT32 mClippedContentWidth, mClippedContentHeight;
		UINT32 mContentWidth, mContentHeight;

		static const UINT32 ScrollBarWidth;
		static const UINT32 MinHandleSize;
		static const UINT32 WheelScrollAmount;

	};
}