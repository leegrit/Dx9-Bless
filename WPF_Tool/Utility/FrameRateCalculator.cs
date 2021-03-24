using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Threading;
using System.Windows.Media;

namespace WPF_Tool.Utility
{
    public class FrameRateCalculator
    {
        private int m_frameCount = 0;
        private int m_frameRate = 0;
        private TimeSpan m_timeSpanElapsed ;
        private DateTime m_dateTimeNow ;
        private DateTime m_dateTimeLastTick ;
        private TimeSpan m_totalElapsedTime ;
        public FrameRateCalculator()
        {
            m_dateTimeLastTick = DateTime.Now;
        }
        public void Tick()
        {
            m_frameCount++;

            // 현재 시간
            m_dateTimeNow = DateTime.Now;

            // 경과시간 : 지금시간 - 마지막 시간
            m_timeSpanElapsed = m_dateTimeNow - m_dateTimeLastTick;
            // 마지막 시간 기록
            m_dateTimeLastTick = m_dateTimeNow;

            m_totalElapsedTime += m_timeSpanElapsed;

            if (m_totalElapsedTime.TotalMilliseconds > 1000)
            {
                m_totalElapsedTime = TimeSpan.Zero;
                m_frameRate = m_frameCount;
                m_frameCount = 0;
            }
        }
        public int GetFrameRate()
        {
            return m_frameRate;
        }
        public TimeSpan GetElapsedTime()
        {
            return m_timeSpanElapsed;
        }
    }
}
