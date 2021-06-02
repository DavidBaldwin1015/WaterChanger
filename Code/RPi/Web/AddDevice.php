<!DOCTYPE html>
<html>
<head>
	<!--- Load the necessary Ajax library and JavaScript functions --->
	<meta name="viewport" content="width=device-width, inital-scale=1.0">
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
	<script src="jQueryFunctions.js"></script>
</head>
<body>
	<!--- Build the navigation menu --->
	<ul id="NavMenu">
		<li><a href="index.php"><div class="Tips"><span class="TipText">Dashboard</span></div></a></li>
		<li><a href="Tanks.php"><div class="Tips"><span class="TipText">Tanks and Valves</span></div></a></li>
		<li><a href="Pumps.php"><div class="Tips"><span class="TipText">Pump Controls</span></div></a></li>
		<li><a href="Flows.php"><div class="Tips"><span class="TipText">Flowmeters</span></div></a></li>
		<li><a href="Manual.php"><div class="Tips"><span class="TipText">Manual Override</span></div></a></li>
	</ul>
	<!--- Build the form to add a device --->
	<form class="AddDeviceForm" id = "NewDeviceForm">
		<label for="DeviceName">Device name:</label><br>
		<input type="text" name="DeviceName"><br>
		<!--- Take input as a drp down menu --->
		<label for="DeviceType">Device type:</label><br>
		<select name="DeviceType" id="DeviceTypeSelect" form="NewDeviceForm" required>
			<option value = "Valve"> Valve </option>
			<option value = "Tank"> Tank </option>
			<option value = "Pump"> Pump </option>
			<option value = "FlowMeter"> Flow Meter </option>
			<option value = "Float"> Float Switch </option>
			<option value = "Other"> Other </option>
		</select>
		<!--- Ask some binary questions --->
		<p> Analog or digital: </p><br>
		<input type="radio" name="AD" id="Analog" value = "Analog">
		<label for="Analog">Analog</label>
		<input type="radio" name="AD" id="Digital" value = "Digital">
		<label for="Digital"></label><br>
		<p> Input or Output: </p><br>
		<input type="radio" id="Input" name="InOut" value="Input">
		<label for="Input">Input</label><br>
		<input type="radio" id="Output" name="InOut" value="Output">
		<label for="Output">Output</label><br>
		<p> Initial Status: </p><br>
		<input type="radio" id="On" name="Status" value="On">
		<label for="On">On</label>
		<input type="radio" id="Off" name="Status" value="Off">
		<label for="Off">Off</label><br>
		<!---Set up an autopopulating dropdown menu for pin assignments --->
		<select name="Pin" id="Pins" >
		</select>
	</form>
</body>
</html>