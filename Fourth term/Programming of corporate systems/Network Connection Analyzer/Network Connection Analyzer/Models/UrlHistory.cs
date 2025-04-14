using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Network_Connection_Analyzer.Models
{
    public class UrlHistory
    {
        public int Id { get; set; }
        public string ?Url { get; set; }
        public DateTime CheckedAt { get; set; }
    }
}
