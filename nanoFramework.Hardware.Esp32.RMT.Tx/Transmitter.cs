using System;
using System.Runtime.CompilerServices;

namespace nanoFramework.Hardware.Esp32.RMT.Tx
{
	/// <summary>
	/// Wraper C# to esp32-idf RTM API (Tx only)
	/// </summary>
	public class Transmitter : IDisposable
	{
		/*
		// доступное апи : https://github.com/espressif/esp-idf/blob/39f090a4f/components/driver/include/driver/rmt.h
		// делитель +
		esp_err_t rmt_set_clk_div(rmt_channel_t channel, uint8_t div_cnt);

		// получить делитель +
		esp_err_t rmt_get_clk_div(rmt_channel_t channel, uint8_t* div_cnt);

		// связать канал с выделенным блоком памяти размером 64 * 32 bits.
		esp_err_t rmt_set_mem_block_num(rmt_channel_t channel, uint8_t rmt_mem_num);

		// настроить модуляцию
		esp_err_t rmt_set_tx_carrier(rmt_channel_t channel, bool carrier_en, uint16_t high_level, uint16_t low_level, rmt_carrier_level_t carrier_level);

		// перевезти память в пониженное энергопоребление
		esp_err_t rmt_set_mem_pd(rmt_channel_t channel, bool pd_en);

		// память в лоу павер моде?
		esp_err_t rmt_get_mem_pd(rmt_channel_t channel, bool* pd_en);

		// начать передачу
		esp_err_t rmt_tx_start(rmt_channel_t channel, bool tx_idx_rst);

		// прервать передачу
		esp_err_t rmt_tx_stop(rmt_channel_t channel);

		// сброс указателя приема/передачи
		esp_err_t rmt_memory_rw_rst(rmt_channel_t channel);

		// установить вледение буфером ???
		esp_err_t rmt_set_memory_owner(rmt_channel_t channel, rmt_mem_owner_t owner);

		// получить владельца буфера
		esp_err_t rmt_get_memory_owner(rmt_channel_t channel, rmt_mem_owner_t* owner);

		// установить циклический режим передачи +
		esp_err_t rmt_set_tx_loop_mode(rmt_channel_t channel, bool loop_en);

		// циклический режим? +
		esp_err_t rmt_get_tx_loop_mode(rmt_channel_t channel, bool* loop_en);

		// установить источник опорной частоты пердетчика +
		esp_err_t rmt_set_source_clk(rmt_channel_t channel, rmt_source_clk_t base_clk);

		// получить источник опорной частоты передатчика +
		esp_err_t rmt_get_source_clk(rmt_channel_t channel, rmt_source_clk_t* src_clk);

		// установить уровень, который будет на выходе передатчика при бездействии +
		esp_err_t rmt_set_idle_level(rmt_channel_t channel, bool idle_out_en, rmt_idle_level_t level);

		// получить настройки бездействия +
		esp_err_t rmt_get_idle_level(rmt_channel_t channel, bool* idle_out_en, rmt_idle_level_t* level);

		// получить статус модуля
		esp_err_t rmt_get_status(rmt_channel_t channel, uint32_t* status);

		// установить регистр прерываний модуля ???
		void rmt_set_intr_enable_mask(uint32_t mask);

		// одичстить маски прерываний модуля
		void rmt_clr_intr_enable_mask(uint32_t mask);

		// разрешить прерывание передатчика
		esp_err_t rmt_set_tx_intr_en(rmt_channel_t channel, bool en);

		// разрешить прерывание по выполнении определенного evt_thresh процента работы предатчиком
		esp_err_t rmt_set_tx_thr_intr_en(rmt_channel_t channel, bool en, uint16_t evt_thresh);

		// подключить пин к каналу РМТ в режиме RX или TX
		esp_err_t rmt_set_pin(rmt_channel_t channel, rmt_mode_t mode, gpio_num_t gpio_num);

		// настроить модуль согласно структуре
		esp_err_t rmt_config(const rmt_config_t* rmt_param);

		// зарегистрировать прерывание
		esp_err_t rmt_isr_register(void (* fn)(void* ), void* arg, int intr_alloc_flags, rmt_isr_handle_t* handle);

		// снять регистрацию прерывания
		esp_err_t rmt_isr_deregister(rmt_isr_handle_t handle);

		// наполнить буфер передатчика данными
		esp_err_t rmt_fill_tx_items(rmt_channel_t channel, const rmt_item32_t* item, uint16_t item_num, uint16_t mem_offset);

		// инициализировать канал RMT
		esp_err_t rmt_driver_install(rmt_channel_t channel, size_t rx_buf_size, int intr_alloc_flags);

		// деинициализировать канал RMT
		esp_err_t rmt_driver_uninstall(rmt_channel_t channel);

		// статус всех каналов
		esp_err_t rmt_get_channel_status(rmt_channel_status_result_t* channel_status);

		// высокоуровневая функция передачи, блокирующая или нет.
		esp_err_t rmt_write_items(rmt_channel_t channel, const rmt_item32_t* rmt_item, int item_num, bool wait_tx_done);

		// блокирует поток до того как передача завершится
		esp_err_t rmt_wait_tx_done(rmt_channel_t channel, TickType_t wait_time);

		// получить кольцевой буфер ??
		esp_err_t rmt_get_ringbuf_handle(rmt_channel_t channel, RingbufHandle_t* buf_handle);

		// установить коллбэк, который коныертирует данные в буфере в данные , пригодные для RMT
		esp_err_t rmt_translator_init(rmt_channel_t channel, sample_to_rmt_t fn);

		// ???
		esp_err_t rmt_write_sample(rmt_channel_t channel, const uint8_t* src, size_t src_size, bool wait_tx_done);

		// Установить колбэк, который будет вызван по окончании передачи
		rmt_tx_end_callback_t rmt_register_tx_end_callback(rmt_tx_end_fn_t function, void* arg);
		*/

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

		public void Dispose()
		{
			Dispose(true);
			GC.SuppressFinalize(this);
		}

		protected virtual void Dispose(bool disposing)
		{
			NativeDispose(Channel);
		}

		private void ConfigureCarier() => NativeSetCarioerMode(Channel, CarierEnabled, CarierHighLevel, CarierLowLevel, CarierHighLvl);

		public void SendData(byte[] data) => NativeSendData(Channel, data);

		#endregion Methods

		#region Destructors

		~Transmitter()
		{
			Dispose(false);
		}

		#endregion Destructors

		#region Constructors

		private Transmitter(int channel)
		{
			Channel = channel;
		}

		#endregion Constructors

		#region Fields

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
			set => NativeSetClockDiv(Channel, value);
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
		/// Setup transmission loop mode
		/// </summary>
		/// <ref>https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/rmt.html#_CPPv420rmt_get_tx_loop_mode13rmt_channel_tPb</ref>
		public bool LoopTxMode
		{
			get => NativeGetLoopTxMode(Channel);
			set => NativeSetLoopTxMode(Channel, value);
		}

		/// <summary>
		/// Configure Transmitter idle output level
		/// </summary>
		/// <value="-1">Output is disabled</value>
		/// <value="0">Output as 0</value>
		/// <value="0">Output as 0</value>
		/// <ref>https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/rmt.html#_CPPv418rmt_set_idle_level13rmt_channel_tb16rmt_idle_level_t</ref>
		public sbyte TransmitterIdleLevel
		{
			get
			{
				bool lvl = false;
				bool enabled = false;
				NativeGetTransmitterIdleLevel(Channel, ref enabled, ref lvl);
				return enabled
					? (lvl ? (sbyte)1 : (sbyte)0)
					: (sbyte)-1;
			}
			set
			{
				bool lvl = value > 0 ;
				bool enabled = value >= 0;
				NativeSetTransmitterIdleLevel(Channel, enabled, lvl);
			}
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
		private static extern bool NativeGetLoopTxMode(int channel);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void NativeGetTransmitterIdleLevel(int channel, ref bool enabled, ref bool lvl);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern int NativeInit(int putputGPIO);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern bool NativeIsSource80MHz(int channel);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void NativeSetClockDiv(int channel, byte value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void NativeSetLoopTxMode(int channel, bool value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void NativeSetSource80MHz(int channel, bool value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void NativeSetTransmitterIdleLevel(int channel, bool enabled, bool lvl);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void NativeSetCarioerMode(int channel, bool carier_en, UInt16 high_lvl, UInt16 low_level, bool carier_ar_one);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void NativeSendData(int channel, byte[] data);

		#endregion Stubs
	}
}