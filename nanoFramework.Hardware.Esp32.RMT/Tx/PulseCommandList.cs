using System.Collections;

namespace nanoFramework.Hardware.Esp32.RMT.Tx
{
	public class PulseCommandList : IPulseCommandList
	{
		#region Fields

		/// <summary>
		/// List of pulse commands
		/// </summary>
		protected ArrayList commands = new ArrayList();

		#endregion Fields

		#region Methods

		/// <summary>
		/// Add full command to command list
		/// </summary>
		/// <param name="cmd">initialised Pulse command instance</param>
		/// <returns>self (to chaining calls)</returns>
		public virtual IPulseCommandList AddCommand(PulseCommand cmd)
		{
			commands.Add(cmd);
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
			var result = new byte[commands.Count * PulseCommand.SerialisedSize];
			for (int i = 0, offset = 0; i < commands.Count; ++i, offset += PulseCommand.SerialisedSize)
			{
				((PulseCommand)commands[i]).SerialiseTo(result, offset);
			}
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
			if (commands.Count == 0)
			{
				return null;
			}

			return (PulseCommand)commands[commands.Count - 1];
		}

		#endregion Methods
	}
}