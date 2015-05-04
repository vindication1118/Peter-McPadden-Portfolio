package info.omgwtfhax.IGVindication1118Me.core;
import org.apache.commons.lang.StringUtils;
import org.bukkit.Bukkit;
import org.bukkit.command.Command;
import org.bukkit.command.CommandSender;
import org.bukkit.plugin.java.JavaPlugin;

	public class OWHMe extends JavaPlugin{
		
		public void onEnable(){
			
		}
		
		public void onDisable(){
			
		}
		
		public boolean onCommand(CommandSender sender, Command command, String label, String[] args){
			if(label.equalsIgnoreCase("me")){
			String message = StringUtils.join(args," ");
			String player = sender.getName();
			Bukkit.broadcastMessage(player+" "+message);
			
			return true;
			}
			else{
				return false;
			}
		}
	}


