/*
 val3dity - Copyright (c) 2011-2017, Hugo Ledoux.  All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
     * Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
     * Neither the name of the authors nor the
       names of its contributors may be used to endorse or promote products
       derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL HUGO LEDOUX BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
*/

#include "MultiSolid.h"
#include "input.h"

namespace val3dity
{

MultiSolid::MultiSolid(std::string id) {
  _id = id;
  _is_valid = -1;
}

MultiSolid::~MultiSolid() {
}

Primitive3D MultiSolid::get_type() 
{
  return MULTISOLID;
}

bool MultiSolid::validate(double tol_planarity_d2p, double tol_planarity_normals, double tol_overlap) 
{
  bool isValid = true;
  for (auto& s : _lsSolids)
  {
    if (s->validate(tol_planarity_d2p, tol_planarity_normals) == false)
      isValid = false;
  }
  _is_valid = isValid;
  return isValid;
}


int MultiSolid::is_valid() 
{
  if ( (_is_valid == 1) && (this->is_empty() == false) && (_errors.empty() == true) )
    return 1;
  else
    return _is_valid;
}


void MultiSolid::get_min_bbox(double& x, double& y)
{
  double tmpx, tmpy;
  double minx = 9e10;
  double miny = 9e10;
  for (auto& s : _lsSolids)
  {
    s->get_min_bbox(tmpx, tmpy);
    if (tmpx < minx)
      minx = tmpx;
    if (tmpy < miny)
      miny = tmpy;
  }
  x = minx;
  y = miny;
}


void MultiSolid::translate_vertices()
{
  for (auto& s : _lsSolids)
    s->translate_vertices();
}

bool MultiSolid::is_empty() 
{
  return _lsSolids.empty();
}


json MultiSolid::get_report_json()
{
  json j;
  bool isValid = true;
  j["type"] = "MultiSolid";
  if (this->get_id() != "")
    j["id"] = this->_id;
  else
    j["id"] = "none";
  j["numbersolids"] = this->number_of_solids();
  j["errors"];
  for (auto& err : _errors)
  {
    for (auto& e : _errors[std::get<0>(err)])
    {
      json jj;
      jj["type"] = "Error";
      jj["code"] = std::get<0>(err);
      jj["description"] = errorcode2description(std::get<0>(err));
      jj["id"] = std::get<0>(e);
      jj["info"] = std::get<1>(e);
      j["errors"].push_back(jj);
      isValid = false;
    }
  }
  for (auto& s : _lsSolids)
  {
    j["primitives"].push_back(s->get_report_json());
    if (s->is_valid() == false)
      isValid = false;
  }
  j["validity"] = isValid;
  return j;
}

std::string MultiSolid::get_report_xml() 
{
    std::stringstream ss;
  ss << "\t<MultiSolid>" << std::endl;
  if (this->get_id() != "")
    ss << "\t\t<id>" << this->_id << "</id>" << std::endl;
  else
    ss << "\t\t<id>none</id>" << std::endl;
  ss << "\t\t<numbersolids>" << this->number_of_solids() << "</numbersolids>" << std::endl;
  for (auto& err : _errors)
  {
    for (auto& e : _errors[std::get<0>(err)])
    {
      ss << "\t\t<Error>" << std::endl;
      ss << "\t\t\t<code>" << std::get<0>(err) << "</code>" << std::endl;
      ss << "\t\t\t<type>" << errorcode2description(std::get<0>(err)) << "</type>" << std::endl;
      ss << "\t\t\t<id>" << std::get<0>(e) << "</id>" << std::endl;
      ss << "\t\t\t<info>" << std::get<1>(e) << "</info>" << std::endl;
      ss << "\t\t</Error>" << std::endl;
    }
  }
  for (auto& s : _lsSolids)
    ss << s->get_report_xml();
  ss << "\t</MultiSolid>" << std::endl;
  return ss.str();
}


bool MultiSolid::add_solid(Solid* s) {
  _lsSolids.push_back(s);
  return true;
}

std::set<int> MultiSolid::get_unique_error_codes() {
  std::set<int> errs = Primitive::get_unique_error_codes();
  for (auto& s : _lsSolids) {
    std::set<int> tmp = s->get_unique_error_codes();
    errs.insert(tmp.begin(), tmp.end());
  }
  return errs;
}

int MultiSolid::number_of_solids() {
  return _lsSolids.size();
}

} // namespace val3dity
