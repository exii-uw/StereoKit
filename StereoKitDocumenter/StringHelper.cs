﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StereoKitDocumenter
{
    static class StringHelper
    {
        public static string CleanForDescription(string text)
        {
            return text.Replace('\n', ' ')
                       .Replace('\r', ' ')
                       .Replace(':', '.')
                       .Replace("`", "");
        }

        public static string CleanForTable(string text)
        {
            return text.Replace('\n', ' ')
                       .Replace('\r', ' ');
        }
    }
}