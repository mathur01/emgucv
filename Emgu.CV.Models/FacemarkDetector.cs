﻿//----------------------------------------------------------------------------
//  Copyright (C) 2004-2021 by EMGU Corporation. All rights reserved.       
//----------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Emgu.CV;
using Emgu.CV.CvEnum;
using Emgu.CV.Dnn;
using Emgu.CV.Face;
using Emgu.CV.Structure;
using Emgu.CV.Util;
using Emgu.Util;

namespace Emgu.CV.Models
{
    /// <summary>
    /// Facial landmark detector
    /// </summary>
    public class FacemarkDetector
    {
        private FacemarkLBF _facemark = null;

        public async Task Init(System.Net.DownloadProgressChangedEventHandler onDownloadProgressChanged = null)
        {
            if (_facemark == null)
            {
                FileDownloadManager manager = new FileDownloadManager();
                manager.AddFile(
                    "https://raw.githubusercontent.com/kurnianggoro/GSOC2017/master/data/lbfmodel.yaml", 
                    "facemark",
                    "70DD8B1657C42D1595D6BD13D97D932877B3BED54A95D3C4733A0F740D1FD66B");
                if (onDownloadProgressChanged != null)
                    manager.OnDownloadProgressChanged += onDownloadProgressChanged;
                await manager.Download();
                if (manager.AllFilesDownloaded)
                {
                    using (FacemarkLBFParams facemarkParam = new CV.Face.FacemarkLBFParams())
                    {
                        _facemark = new FacemarkLBF(facemarkParam);
                        _facemark.LoadModel(manager.Files[0].LocalFile);
                    }
                } 
            }
        }

        public VectorOfVectorOfPointF Detect(Mat image, Rectangle[] fullFaceRegions)
        {
            using (VectorOfRect vr = new VectorOfRect(fullFaceRegions))
            {
                VectorOfVectorOfPointF landmarks = new VectorOfVectorOfPointF();
                _facemark.Fit(image, vr, landmarks);
                return landmarks;
            }
        }
    }
}
