using System;

namespace nanoFramework.Hardware.Esp32.RMT.Tx
{
	// see examples/peripherals/rmt_tx/main/rmt_tx_main.c for more info
	public interface IPulseCommandList
	{
		/// <summary>
		/// Add state to pulse chain
		/// If possible, combine with the previous
		/// </summary>
		/// <param name="state">State to hold</param>
		/// <param name="Duration">Time to hold state in chanks</param>
		/// <returns>self</returns>
		IPulseCommandList AddState(bool state, UInt16 Duration);

		/// <summary>
		/// Add full command to list
		/// </summary>
		/// <param name="cmd">initialised Pulse command instance</param>
		/// <returns>self</returns>
		IPulseCommandList AddCommand(PulseCommand cmd);

		/// <summary>
		/// Generate list of rmt_item32_t (esp-idf-v3.1/components/soc/esp32/include/soc/rmt_struct.h : 234)
		/// </summary>
		/// <returns>bytearray, represents command list for native code</returns>
		byte[] Serialise();
	}
}
