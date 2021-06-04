<!DOCTYPE html>
<html>
<head>
	<!--- Load the necessary Ajax library and JavaScript functions --->
	<meta name="viewport" content="width=device-width, inital-scale=1.0">
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
	<script src="jQueryFunctions.js"></script>
	<link rel="stylesheet" href="Styles.css">
</head>
<body>
	<!--- Build the navigation menu --->
	<ul id="NavMenu">
		<li><a href="index.php"><img src="monitor-outline.png" id="DashboardIcon"/><div class="tooltip"><span class="tooltiptext">Dashboard</span></div></a></li>
		<li><a href="Tanks.php"><div class="tooltip"><span class="tooltiptext">Tanks and Valves</span></div></a></li>
		<li><a href="Pumps.php"><div class="tooltip"><span class="tooltiptext">Pump Controls</span></div></a></li>
		<li><a href="Flows.php"><div class="tooltip"><span class="tooltiptext">Flowmeters</span></div></a></li>
		<li><a href="Manual.php"><div class="tooltip"><span class="tooltiptext">Manual Override</span></div></a></li>
	</ul><br>
	<div id="content">
	<!--- Build the form to add a device --->
	<form class="AddDeviceForm" id = "NewDeviceForm">
		<label for="DeviceName">Device name:</label><br>
		<input type="text" name="DeviceName" id="DevName"><br>
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
		<label for="Digital">Digital</label><br>
		<p> Input or Output: </p><br>
		<input type="radio" id="Input" name="InOut" value="Input">
		<label for="Input">Input</label><br>
		<input type="radio" id="Output" name="InOut" value="Output">
		<label for="Output">Output</label><br>
		<!---Set up an autopopulating dropdown menu for pin assignments --->
		<p> Which pin will this be connected to? </p>
		<select name="Pin" id="Pins" >
		</select>
		<p> Initial Status: </p><br>
		<input type="radio" id="On" name="Status" value="On">
		<label for="On">On</label>
		<input type="radio" id="Off" name="Status" value="Off">
		<label for="Off">Off</label><br>
		<input type="button" id="submit" text="Add Device">
	</form>
	<div id="SuccessMessage">
		<span> Device successfully added. </span>
	</div>
</div>
</body>
</html>