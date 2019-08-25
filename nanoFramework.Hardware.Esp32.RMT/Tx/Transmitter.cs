using System;
using System.Runtime.CompilerServices;

namespace nanoFramework.Hardware.Esp32.RMT.Tx
{
	/// <summary>
	/// Wraper C# to esp32-idf RTM API (Tx only)
	/// </summary>
	public class Transmitter : IDisposable
	{
		#region Methods

		/// <summary>
		/// Creare new RTM transmitter and connect it to designed GPIO pin number
		/// </summary>
		/// <param name="GPIO"></param>
		/// <returns></returns>
		public static Transmitter Register(int GPIO)
		{
			int channel = NativeInit(GPIO);
			if (channel < 0)
			{
				throw new NotSupportedException($"Can't find RTM channels avalable, or can't connect co pin ${GPIO}");
			}
			return new Transmitter(channel);
		}

		/// <summary>
		/// Dispose transmitter object, also shut down native driver for used channel
		/// </summary>
		public void Dispose()
		{
			Dispose(true);
			GC.SuppressFinalize(this);
		}

		/// <summary>
		/// Send a RAW data to RMT module, returns indien, but waits while previes are fully transmitted
		/// </summary>
		/// <param name="data">Byte array, that contains list of serialized structs rmt_item32_t</param>
		public void SendData(byte[] data) => NativeSendData(Channel, data);

		/// <summary>
		/// Send IPulseCommandList to RMT module
		/// simply do SendData(commandlist.Serialise())
		/// </summary>
		/// <param name="commandlist">Command list for RMT module</param>
		public void Send(IPulseCommandList commandlist) => SendData(commandlist.Serialise());

		protected virtual void Dispose(bool disposing) => NativeDispose(Channel);

		private void ConfigureCarier() => NativeSetCarierMode(Channel, CarierEnabled, CarierHighLevel, CarierLowLevel, CarierHighLvl);

		#endregion Methods

		#region Destructors

		~Transmitter() => Dispose(false);

		#endregion Destructors

		#region Constructors

		private Transmitter(int channel)
		{
			Channel = channel;

			ConfigureCarier();
		}

		#endregion Constructors

		#region Fields

		/// <summary>
		/// Single RMT command size
		/// </summary>
		internal const uint rmt_command_size = PulseCommand.SerialisedSize;

		private readonly bool mCarierEnabled = false;
		private readonly UInt16 mCarierHighLevel = 1;
		private readonly bool mCarierHighLvl = false;
		private readonly UInt16 mCarierLowLevel = 1;
		private int mChannel;

		#endregion Fields

		#region Properties

		/// <summary>
		/// Is carrier enabled?
		/// </summary>
		public bool CarierEnabled
		{
			get => mCarierEnabled;
			set => ConfigureCarier();
		}

		/// <summary>
		/// Get used RTM channel number
		/// </summary>
		public int Channel { get => mChannel; private set => mChannel = value; }

		/// <summary>
		/// Setup RTM channel clock sevider
		/// </summary>
		/// <ref>https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/rmt.html#_CPPv415rmt_set_clk_div13rmt_channel_t7uint8_t</ref>
		public byte ClockDivider
		{
			get => NativeGetClockDiv(Channel);
			set {
				if (value == 0)
				{
					throw new ArgumentOutOfRangeException("1..255");
				}
				NativeSetClockDiv(Channel, value);
			}
		}

		/// <summary>
		/// RTM source CLK
		/// </summary>
		/// <value="true">Source lock is APB 80MHz</value>
		/// <valu="false">Source lock is REF tick clock, which would be 1Mhz (not supported in this version).</valu>
		public bool isSource80MHz
		{
			get => NativeIsSource80MHz(Channel);
			set => NativeSetSource80MHz(Channel, value);
		}

		/// <summary>
		/// Enable transmirtter holding idle level
		/// </summary>
		/// <ref>https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/rmt.html#_CPPv418rmt_set_idle_level13rmt_channel_tb16rmt_idle_level_t</ref>
		public bool IsTransmitIdleEnabled
		{
			get => NativeIsTransmitIdleEnabled(Channel);
			set => NativeSetTransmitIdleEnabled(Channel, value);
		}

		/// <summary>
		/// Transmitter idle level (if enabled)
		/// </summary>
		public bool TransmitIdleLevel
		{
			get => NativeGetTransmitIdleLevel(Channel);
			set => NativeSetTransmitIdleLevel(Channel, value);
		}

		/// <summary>
		/// Carier High level duration
		/// </summary>
		/// <ref>https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/rmt.html#_CPPv418rmt_set_tx_carrier13rmt_channel_tb8uint16_t8uint16_t19rmt_carrier_level_t</ref>
		private UInt16 CarierHighLevel
		{
			get => mCarierHighLevel;
			set => ConfigureCarier();
		}

		/// <summary>
		/// Transmit Carier if outpet level equals 1
		/// </summary>
		/// <value="false">Transmit Carier if outpet level equals 0</value>
		/// <value="true">Transmit Carier if outpet level equals 1</value>
		private bool CarierHighLvl
		{
			get => mCarierHighLvl;
			set => ConfigureCarier();
		}

		/// <summary>
		/// Carier Low level duration
		/// </summary>
		/// <ref>https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/rmt.html#_CPPv418rmt_set_tx_carrier13rmt_channel_tb8uint16_t8uint16_t19rmt_carrier_level_t</ref>
		private UInt16 CarierLowLevel
		{
			get => mCarierLowLevel;
			set => ConfigureCarier();
		}

		#endregion Properties

		#region Stubs

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void NativeDispose(int channel);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern byte NativeGetClockDiv(int channel);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern bool NativeGetTransmitIdleLevel(int channel);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern int NativeInit(int putputGPIO);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern bool NativeIsSource80MHz(int channel);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern bool NativeIsTransmitIdleEnabled(int channel);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void NativeSendData(int channel, byte[] data);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void NativeSetCarierMode(int channel, bool carier_en, UInt16 high_lvl, UInt16 low_level, bool carier_ar_one);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void NativeSetClockDiv(int channel, byte value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void NativeSetSource80MHz(int channel, bool value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void NativeSetTransmitIdleEnabled(int channel, bool value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void NativeSetTransmitIdleLevel(int channel, bool value);

		#endregion Stubs
	}
}