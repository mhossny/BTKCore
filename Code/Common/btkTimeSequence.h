/* 
 * The Biomechanical ToolKit
 * Copyright (c) 2009-2015, Arnaud Barré
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *     * Redistributions of source code must retain the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *     * Neither the name(s) of the copyright holders nor the names
 *       of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written
 *       permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __btkTimeSequence_h
#define __btkTimeSequence_h

#include "btkNode.h"

#include <vector>
#include <array>
#include <numeric>

namespace btk
{
  class TimeSequencePrivate;
  
  class BTK_COMMON_EXPORT TimeSequence : public Node
  {
    BTK_DECLARE_PIMPL_ACCESSOR(TimeSequence)
  
  public:
    enum : unsigned {Unknown = 0, Marker, Angle, Force, Moment, Power, Scalar, Analog};
    static constexpr std::array<double,2> InfinityRange{-std::numeric_limits<double>::infinity(),std::numeric_limits<double>::infinity()};
    
    TimeSequence(unsigned component, unsigned samples, const std::string& name, double rate, const std::string& unit, int type = Unknown, double startTime = 0.0, double scale = 1.0, double offset = 0.0, const std::array<double,2>& range = InfinityRange, Node* parent = nullptr);
    TimeSequence(const std::vector<unsigned>& dimensions, unsigned samples, const std::string& name, double rate, const std::string& unit, int type = Unknown, double startTime = 0.0, double scale = 1.0, double offset = 0.0, const std::array<double,2>& range = InfinityRange, Node* parent = nullptr);
    ~TimeSequence() noexcept;
    
    TimeSequence(const TimeSequence& ) = delete;
    TimeSequence(TimeSequence&& ) noexcept = delete;
    TimeSequence& operator=(const TimeSequence& ) = delete;
    TimeSequence& operator=(TimeSequence&& ) noexcept = delete;
    
    double sampleRate() const noexcept;
    void setSampleRate(double value) noexcept;
    
    const std::vector<unsigned>& dimensions() const noexcept;
    unsigned samples() const noexcept;
    unsigned components() const noexcept;
    size_t elements() const noexcept;
    
    double duration() const noexcept;
    
    int type() const noexcept;
    void setType(int value) noexcept;
    
    const std::string& unit() const noexcept;
    void setUnit(const std::string& value) noexcept;
    
    double startTime() const noexcept;
    void setStartTime(double value) noexcept;
    
    double scale() const noexcept;
    void setScale(double value) noexcept;
    
    double offset() const noexcept;
    void setOffset(double value) noexcept;
    
    const std::array<double,2>& range() const noexcept;
    void setRange(const std::array<double,2>& value) noexcept;
    
    const double* data() const noexcept;
    double* data() noexcept;
  };
};

#endif // __btkTimeSequence_h