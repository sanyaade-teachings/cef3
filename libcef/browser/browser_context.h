// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CEF_LIBCEF_BROWSER_BROWSER_CONTEXT_H_
#define CEF_LIBCEF_BROWSER_BROWSER_CONTEXT_H_
#pragma once

#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/content_browser_client.h"
#include "net/url_request/url_request_job_factory.h"

namespace content {
class DownloadManagerDelegate;
class SpeechRecognitionPreferences;
}

class CefDownloadManagerDelegate;
class CefURLRequestContextGetter;

class CefBrowserContext : public content::BrowserContext {
 public:
  CefBrowserContext();
  virtual ~CefBrowserContext();

  // BrowserContext methods.
  virtual base::FilePath GetPath() const OVERRIDE;
  virtual bool IsOffTheRecord() const OVERRIDE;
  virtual content::DownloadManagerDelegate* GetDownloadManagerDelegate() OVERRIDE;
  virtual net::URLRequestContextGetter* GetRequestContext() OVERRIDE;
  virtual net::URLRequestContextGetter* GetRequestContextForRenderProcess(
      int renderer_child_id) OVERRIDE;
  virtual net::URLRequestContextGetter* GetMediaRequestContext() OVERRIDE;
  virtual net::URLRequestContextGetter* GetMediaRequestContextForRenderProcess(
      int renderer_child_id) OVERRIDE;
  virtual net::URLRequestContextGetter*
      GetMediaRequestContextForStoragePartition(
          const base::FilePath& partition_path,
          bool in_memory) OVERRIDE;
  virtual void RequestMIDISysExPermission(
      int render_process_id,
      int render_view_id,
      const GURL& requesting_frame,
      const MIDISysExPermissionCallback& callback) OVERRIDE;
  virtual content::ResourceContext* GetResourceContext() OVERRIDE;
  virtual content::GeolocationPermissionContext*
      GetGeolocationPermissionContext() OVERRIDE;
  virtual quota::SpecialStoragePolicy* GetSpecialStoragePolicy() OVERRIDE;

  net::URLRequestContextGetter* CreateRequestContext(
      content::ProtocolHandlerMap* protocol_handlers);
  net::URLRequestContextGetter* CreateRequestContextForStoragePartition(
      const base::FilePath& partition_path,
      bool in_memory,
      content::ProtocolHandlerMap* protocol_handlers);

  // To disable window rendering call this function with |override|=true
  // just before calling WebContents::Create. This will cause
  // CefContentBrowserClient::OverrideCreateWebContentsView to create
  // a windowless WebContentsView object.
  void set_use_osr_next_contents_view(bool override);
  bool use_osr_next_contents_view() const;

 private:
  class CefResourceContext;

  scoped_ptr<CefResourceContext> resource_context_;
  scoped_ptr<CefDownloadManagerDelegate> download_manager_delegate_;
  scoped_refptr<CefURLRequestContextGetter> url_request_getter_;
  scoped_refptr<content::GeolocationPermissionContext>
      geolocation_permission_context_;

  bool use_osr_next_contents_view_;

  DISALLOW_COPY_AND_ASSIGN(CefBrowserContext);
};

#endif  // CEF_LIBCEF_BROWSER_BROWSER_CONTEXT_H_
