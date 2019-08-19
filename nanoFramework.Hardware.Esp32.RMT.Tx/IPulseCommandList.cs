using System;

namespace nanoFramework.Hardware.Esp32.RMT.Tx
{
	public interface IPulseCommandList
	{
		/// <summary>
		/// Add pulse to the list
		/// </summary>
		/// <param name="duration0">utput 0 for duration0 base time chanks</param>
		/// <param name="duration1">utput 1 for duration0 base time chanks</param>
		/// <returns>self</returns>
		IPulseCommandList AddPulse(UInt16 duration0, UInt16 duration1);

		/// <summary>
		/// Add state to pulse chain
		/// If possible, combine with the previous
		/// </summary>
		/// <param name="state">State to hold</param>
		/// <param name="Duration">Time to hold state in chanks</param>
		/// <returns></returns>
		IPulseCommandList AddState(bool state, UInt16 Duration);

		/// <summary>
		/// Generate list of rmt_item32_t (esp-idf-v3.1/components/soc/esp32/include/soc/rmt_struct.h : 234)
		/// </summary>
		/// <returns></returns>
		byte[] Serialise();
	}
}
