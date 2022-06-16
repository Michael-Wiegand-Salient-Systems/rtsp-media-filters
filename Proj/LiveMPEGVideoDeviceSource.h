/**********
This library is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the
Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version. (See <http://www.gnu.org/copyleft/lesser.html>.)

This library is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General Public License
along with this library; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
**********/
// "CSIR"
// Copyright (c) 2014 CSIR.  All rights reserved.
///
/// @class LiveMPEGVideoDeviceSource
///
/// Modified 08/16/2019
/// Modified by: M. Kinzer
///

#pragma once

#include "LiveDeviceSource.h"
#include "CommonRtsp.h"

namespace CvRtsp
{
	class LiveMPEGVideoDeviceSource : public LiveDeviceSource
	{
	public:
		///
		/// Destructor.
		virtual ~LiveMPEGVideoDeviceSource() = default;

		///
		/// Named constructor.
		///
		/// @param env						Usage environment.
		/// @param clientId					Client identifier.
		/// @param parentSubsession			Live media subsession parent class.
		/// @param frameGrabber				Frame grabber.
		/// @param rateAdaptationFactory	Rate adaptation factory.
		/// @param globalRateControl		Rate controller.
		///
		/// @return Live video device source.
		static LiveMPEGVideoDeviceSource* CreateNew(UsageEnvironment& env, unsigned clientId,
			LiveMediaSubsession* parentSubsession, IFrameGrabber* frameGrabber, IRateAdaptationFactory* rateAdaptationFactory,
			IRateController* globalRateControl);

		///
		/// Method to add data to the device. Overridden from LiveDeviceSource base class.
		///
		/// @return True	Is media sample is retrieved from the buffer.
		bool RetrieveMediaSampleFromBuffer() override;

	protected:
		///
		/// Default constructor.
		///
		/// @param env						Usage environment.
		/// @param clientId					Client identifier.
		/// @param parentSubsession			Live media subsession parent class.
		/// @param frameGrabber				Frame grabber.
		/// @param rateAdaptationFactory	Rate adaptation factory.
		/// @param globalRateControl		Rate controller.
		LiveMPEGVideoDeviceSource(UsageEnvironment& env, unsigned clientId,
			LiveMediaSubsession* parentSubsession, IFrameGrabber* frameGrabber,
			IRateAdaptationFactory* rateAdaptationFactory, IRateController* globalRateControl);

	private:
		/// 
		/// Checks if this is an I-frame for mpeg coded frame. (2 bits after the vop_start_code)
		///
		/// @param[in] dataBuffer   Pointer to frame buffer, to search in.
		/// @param[in] bufferSize	Size of buffer.
		/// @param[in] offset		Starting position where search begins.
		/// @return    true			If this is I-frame.
		bool checkIsKeyFrame(const BYTE* dataBuffer, uint32_t bufferSize, int offset);

		// --- Data
				/// True if waiting for I-frame.
		bool m_isWaitingForKeyFrame;

		///
		/// Split the payload into multiple media samples for sending via live555 pipeline.
		///
		/// @param dataBuffer	Data to be sent.
		/// @param bufferSize	Size of the data buffer.
		/// @startTime Media	sample start time.
		///
		/// @return Queue of media samples.
		std::deque<std::shared_ptr<MediaSample>> splitPayloadIntoMediaSamples(BYTE* dataBuffer,
			uint32_t bufferSize, double startTime);
	};
}
