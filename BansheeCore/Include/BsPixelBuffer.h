//__________________________ Banshee Project - A modern game development toolkit _________________________________//
//_____________________________________ www.banshee-project.com __________________________________________________//
//________________________ Copyright (c) 2014 Marko Pintera. All rights reserved. ________________________________//
#pragma once

#include "BsCorePrerequisites.h"
#include "BsHardwareBuffer.h"
#include "BsPixelUtil.h"

namespace BansheeEngine 
{
	/**
	 * @brief	Represents a hardware buffer that stores a single pixel surface.
	 *			This may be a 1D, 2D or 3D surface, but unlike a texture it consists
	 *			only of a single surface (no mip maps, cube map faces or similar).
	 *
	 * @note	Core thread only
	 */
    class BS_CORE_EXPORT PixelBuffer : public HardwareBuffer
    {
    public:
		/**
		 * @brief	Constructs a new pixel buffer with the provided settings.
		 *
		 * @param	width			Width of the pixel buffer in pixels.
		 * @param	height			Height of the pixel buffer in pixels.
		 * @param	depth			Depth of the pixel buffer in pixels (number of 2D slices).
		 * @param	format			Format of each pixel in the buffer.
		 * @param	usage			Usage signaling the render system how we plan on using the buffer.
		 * @param	useSystemMemory	True if buffer should be allocated in system memory.
		 */
        PixelBuffer(UINT32 width, UINT32 height, UINT32 depth, PixelFormat format, 
			GpuBufferUsage usage, bool useSystemMemory);
        ~PixelBuffer();

		// Make the other lock overloads visible.
        using HardwareBuffer::lock;	

		/**
		 * @brief	Locks a certain region of the pixel buffer for reading and returns a pointer
		 *			to the locked region.
		 *
		 * @param	lockBox		Region of the surface to lock.
		 * @param	options		Lock options that hint the hardware on what you intend to do with the locked data.
		 *
		 * @note	Returned object is only valid while the lock is active.
		 */
		virtual const PixelData& lock(const PixelVolume& lockBox, GpuLockOptions options);
		
		/**
		 * @copydoc	HardwareBuffer::lock
		 */
        virtual void* lock(UINT32 offset, UINT32 length, GpuLockOptions options);
		
		/**
		 * @copydoc	HardwareBuffer::readData
		 */
		virtual void readData(UINT32 offset, UINT32 length, void* pDest);

		/**
		 * @copydoc	HardwareBuffer::writeData
		 */
		virtual void writeData(UINT32 offset, UINT32 length, const void* pSource, BufferWriteType writeFlags = BufferWriteType::Normal);

		/**
		 * @brief	Returns width of the surface in pixels.
		 */
        UINT32 getWidth() const { return mWidth; }

		/**
		 * @brief	Returns height of the surface in pixels.
		 */
        UINT32 getHeight() const { return mHeight; }

		/**
		 * @brief	Returns depth of the surface in pixels.
		 */
        UINT32 getDepth() const { return mDepth; }

		/**
		 * @brief	Returns format of the pixels in the surface.
		 */
        PixelFormat getFormat() const { return mFormat; }

	protected:
		friend class RenderTexture;

		/**
		 * @brief	Internal implementation of the "lock" method.
		 */
		virtual PixelData lockImpl(PixelVolume lockBox, GpuLockOptions options) = 0;

		/**
		 * @copydoc	HardwareBuffer::lockImpl
		 */
		virtual void* lockImpl(UINT32 offset, UINT32 length, GpuLockOptions options);

	protected:
		UINT32 mWidth, mHeight, mDepth;
		UINT32 mRowPitch, mSlicePitch;
		PixelFormat mFormat;

		PixelData mCurrentLock;
		PixelVolume mLockedBox;
    };
}