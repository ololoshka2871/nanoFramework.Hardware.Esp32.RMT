using System;
using System.Runtime.CompilerServices;

namespace nanoFramework.Hardware.Esp32.RMT.Tx
{
	public class PulseCommandList : IPulseCommandList
	{
		#region Constructors

		public PulseCommandList() => NativeInit();

		/// <summary>
		/// Create new Command list with size empty commands
		/// </summary>
		/// <param name="size">Predefined size (extandable)</param>
		public PulseCommandList(int size)
		{
			NativeInit();
			while (size-- > 0)
			{
				AddCommand(new PulseCommand());
			}
		}

		#endregion Constructors

		#region Destructors

		~PulseCommandList() => Dispose(false);

		#endregion Destructors

		#region Properties

		private int CommandCount => NativeGetCommandCount();

		#endregion Properties

		#region Methods

		public void Dispose()
		{
			Dispose(true);
			GC.SuppressFinalize(this);
		}

		protected virtual void Dispose(bool disposing) => NativeFree();

		public PulseCommand this[int i]
		{
			get
			{
				var res = NativeGetElement(i);
				return (PulseCommand)res;
			}

			set => ((PulseCommand)NativeGetElement(i)).Assign(value);
		}

		/// <summary>
		/// Add full command to command list
		/// </summary>
		/// <param name="cmd">initialised Pulse command instance</param>
		/// <returns>self (to chaining calls)</returns>
		public virtual IPulseCommandList AddCommand(PulseCommand cmd)
		{
			NativeCommandAdd(cmd);
			return this;
		}

		/// <summary>
		/// Add state to pulse chain
		/// If possible, combineed with the previous state
		/// </summary>
		/// <param name="state">State to hold</param>
		/// <param name="Duration">Time to hold state in chanks</param>
		/// <returns>self (to chaining calls)</returns>
		public virtual IPulseCommandList AddLevel(bool level, ushort duration)
		{
			var last_command = LastCommand();
			if (last_command == null)
			{
				AddCommand(level, duration);
			}
			else
			{
				var res = last_command.AddLevel(level, ref duration);
				if (res != PulseCommand.ApplyResult.DONE)
				{
					AddCommand(level, duration);
				}
			}
			return this;
		}

		/// <summary>
		/// Generate list of structs rmt_item32_t ([esp32-idf]/components/soc/esp32/include/soc/rmt_struct.h : 234)
		/// packed into byte array
		/// </summary>
		/// <returns>bytearray, represents command list for native code</returns>
		public virtual byte[] Serialise()
		{
			var result = new byte[CommandCount * PulseCommand.SerialisedSize];
			NativeSerialiseTo(result);
			return result;
		}

		/// <summary>
		/// Add half used command from state
		/// </summary>
		/// <param name="level">output logick level</param>
		/// <param name="Duration">Value duration</param>
		protected void AddCommand(bool level, ushort Duration) =>
			AddCommand(new PulseCommand(Duration, level, 0, level));

		/// <summary>
		/// Get last pulse command in chain
		/// </summary>
		/// <returns>Lat command of chain ir nill if chain is empty</returns>
		protected PulseCommand LastCommand()
		{
			var r = NativeLastCommand();
			return (PulseCommand)r;
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private extern void NativeCommandAdd(object cmd);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private extern void NativeFree();

		[MethodImpl(MethodImplOptions.InternalCall)]
		private extern int NativeGetCommandCount();

		[MethodImpl(MethodImplOptions.InternalCall)]
		private extern void NativeInit();

		[MethodImpl(MethodImplOptions.InternalCall)]
		private extern object NativeLastCommand();

		[MethodImpl(MethodImplOptions.InternalCall)]
		private extern void NativeSerialiseTo(byte[] result);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private extern object NativeGetElement(int index);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private extern void NativeSetCommand(int index, object value);

		#endregion Methods
	}
}