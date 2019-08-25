using System;

namespace nanoFramework.Hardware.Esp32.RMT.Tx
{
	/// <summary>
	/// RMT module command chain
	/// 
	/// see [esp32-idf]/examples/peripherals/rmt_tx/main/rmt_tx_main.c for more info
	/// </summary>
	public interface IPulseCommandList : IDisposable
	{
		/// <summary>
		/// Add state to pulse chain
		/// If possible, combineed with the previous state
		/// </summary>
		/// <param name="state">State to hold</param>
		/// <param name="Duration">Time to hold state in chanks</param>
		/// <returns>self</returns>
		IPulseCommandList AddLevel(bool state, UInt16 Duration);

		/// <summary>
		/// Add full command to command list
		/// </summary>
		/// <param name="cmd">initialised Pulse command instance</param>
		/// <returns>self</returns>
		IPulseCommandList AddCommand(PulseCommand cmd);

		/// <summary>
		/// Generate list of structs rmt_item32_t ([esp32-idf]/components/soc/esp32/include/soc/rmt_struct.h : 234)
		/// packed into byte array
		/// </summary>
		/// <returns>bytearray, represents command list for native code</returns>
		byte[] Serialise();
	}
}
