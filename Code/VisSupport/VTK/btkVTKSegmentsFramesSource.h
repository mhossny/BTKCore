/* 
 * The Biomechanical ToolKit
 * Copyright (c) 2009-2011, Arnaud Barré
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

#ifndef __btkVTKSegmentsFramesSource_h
#define __btkVTKSegmentsFramesSource_h

#include "btkPointCollection.h"

#include <vtkPolyDataAlgorithm.h>
#include <vtkDoubleArray.h>
#include <vtkIntArray.h>
#include <vtkIdTypeArray.h>
#include <vtkLookupTable.h>

#include <vector>

namespace btk
{
  class VTKSegmentsFramesSource : public vtkPolyDataAlgorithm
  {
  public:
    typedef std::pair<int,int> Link;
    
    BTK_VTK_EXPORT static VTKSegmentsFramesSource* New();
    vtkExportedTypeRevisionMacro(VTKSegmentsFramesSource, vtkPolyDataAlgorithm, BTK_VTK_EXPORT);
    BTK_VTK_EXPORT void PrintSelf(ostream& os, vtkIndent indent);

    BTK_VTK_EXPORT void SetInput(PointCollection::Pointer input);
    
    BTK_VTK_EXPORT void AppendDefinition(const std::vector<int>& markerIds, const std::vector<Link>& links);
    BTK_VTK_EXPORT void SetDefinition(vtkIdType id, const std::vector<int>& markerIds, const std::vector<Link>& links);
    BTK_VTK_EXPORT void ClearDefinitions();

    BTK_VTK_EXPORT bool GetSegmentVisibility(vtkIdType id);
    BTK_VTK_EXPORT void SetSegmentVisibility(vtkIdType id, bool visible);
    BTK_VTK_EXPORT double* GetSegmentColor(vtkIdType id);
    BTK_VTK_EXPORT void SetSegmentsColor(vtkIdTypeArray* ids, double r, double g, double b);
    BTK_VTK_EXPORT vtkIdType GetSegmentColorIndex(vtkIdType id);
    BTK_VTK_EXPORT void SetSegmentColorIndex(vtkIdType id, vtkIdType);
    BTK_VTK_EXPORT vtkLookupTable* GetSegmentColorLUT();
    
    BTK_VTK_EXPORT void HideSegment(vtkIdType id);
    BTK_VTK_EXPORT void HideSegments();
    BTK_VTK_EXPORT void ShowSegment(vtkIdType id);
    BTK_VTK_EXPORT void ShowSegments();

    double GetScaleUnit() {return this->mp_Scale;};
    void SetScaleUnit(double s) {this->mp_Scale = s;};
 
  protected:
    BTK_VTK_EXPORT VTKSegmentsFramesSource();
    BTK_VTK_EXPORT ~VTKSegmentsFramesSource();
    
    BTK_VTK_EXPORT virtual int RequestInformation(vtkInformation* request, vtkInformationVector** inputVector, vtkInformationVector* outputVector);
    BTK_VTK_EXPORT virtual int RequestData(vtkInformation* request, vtkInformationVector** inputVector, vtkInformationVector* outputVector);
    //virtual int RequestUpdateExtent(vtkInformation* request, vtkInformationVector** inputVector, vtkInformationVector* outputVector);

    BTK_VTK_EXPORT virtual int FillInputPortInformation(int port, vtkInformation* info);
    
  private:
    VTKSegmentsFramesSource(const VTKSegmentsFramesSource& );  // Not implemented.
    VTKSegmentsFramesSource& operator=(const VTKSegmentsFramesSource& );  // Not implemented.
    
    void constructLinksWithRelativeMarkersId(std::vector<Link>& relLinks, const std::vector<int>& markerIds, const std::vector<Link>& links);
    
    struct SegmentDefinition
    {
      SegmentDefinition(const std::vector<int>& m, const std::vector<Link>& l) : markerIds(m), links(l) {}; 
      std::vector<int> markerIds;
      std::vector<Link> links;
    };
    
    std::list<SegmentDefinition> m_Definitions;
    vtkIntArray* mp_VisibleSegments;
    vtkIdTypeArray* mp_SegmentsColorIndex;
    vtkLookupTable* mp_SegmentsColorsLUT;
    double mp_Scale;
  };
};
#endif // __btkVTKSegmentsFramesSource_h