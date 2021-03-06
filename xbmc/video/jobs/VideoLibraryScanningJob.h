/*
 *      Copyright (C) 2014 Team XBMC
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include <string>

#include "video/VideoInfoScanner.h"
#include "video/jobs/VideoLibraryJob.h"

/*!
 \brief Video library job implementation for scanning items.

 Uses CVideoInfoScanner for the whole filesystem scanning and can be run with
 or without a visible progress bar.
 */
class CVideoLibraryScanningJob : public CVideoLibraryJob
{
public:
  /*!
   \brief Creates a new video library scanning job.

   \param[in] directory Directory to be scanned for new items
   \param[in] scanAll Whether to scan all items or not
   \param[in] showProgress Whether to show a progress bar or not
   */
  CVideoLibraryScanningJob(const std::string& directory, bool scanAll = false, bool showProgress = true);
  ~CVideoLibraryScanningJob() override;

  // specialization of CVideoLibraryJob
  bool CanBeCancelled() const override { return true; }
  bool Cancel() override;

  // specialization of CJob
  const char *GetType() const override { return "VideoLibraryScanningJob"; }
  bool operator==(const CJob* job) const override;

protected:
  // implementation of CVideoLibraryJob
  bool Work(CVideoDatabase &db) override;

private:
  VIDEO::CVideoInfoScanner m_scanner;
  std::string m_directory;
  bool m_showProgress;
  bool m_scanAll;
};
