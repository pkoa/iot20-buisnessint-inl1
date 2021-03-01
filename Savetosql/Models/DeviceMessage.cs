using System;
using System.Collections.Generic;
using System.Text;

namespace Savetosql.Models
{
    public class DeviceMessage
    {
        public string DeviceId { get; set; }
        public float Temperature { get; set; }
        public float Humidity { get; set; }
        public string Formatted_Time { get; set; }
    }
}
