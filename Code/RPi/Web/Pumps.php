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
		<li><a href="index.php"><img src="monitor-outline.png" id="Icon"/><!-- <div class="tooltip"><span class="tooltiptext">Dashboard</span></div> --></a></li>
		<li><a href="Tanks.php"><img src="valve.png" id="Icon"/><!-- <div class="tooltip"><span class="tooltiptext">Tanks and Valves</span></div> -->Tanks and Valves</a></li>
		<li><a href="Pumps.php"><img src="water-pump.png" id="Icon"/><!-- <div class="tooltip"><span class="tooltiptext">Pump Controls</span></div> -->Pumps</a></li>
		<li><a href="Flows.php"><img src="humidity.png" id="Icon"/><!-- <div class="tooltip"><span class="tooltiptext">Flowmeters</span></div> -->Sensors</a></li>
		<!-- <li><a href="Manual.php"><div class="tooltip"><span class="tooltiptext">Manual Override</span></div> Manual Override</a></li> -->
		<li><a href="Admin.php"><img src="double-wrench-outline.png" id="Icon"/> Administration </a></li>
	</ul><br>
	<div id="content">
		<?php
			include('config.php');
			$con = mysqli_connect($host, $username, $password, $database);

			if(!$con){
				die("Connection failed: ".mysqli_connect_error());
			}

			$pumps = mysqli_query($con, "SELECT DeviceName, Status, Pin FROM Devices WHERE DeviceType = 'Pump' AND Active = 1");
			if($pumps){
				echo "<table border=0>
				<tr>
				<th> Pump </th>
				<th> Status </th>
				</tr>";
				while($row=mysqli_fetch_assoc($pumps)){
					$RawStat = $row['Status'];
					echo "<tr>";
					echo "<td>".$row['DeviceName']."</td>";
					if($RawStat == 0){
						echo "<td>"."<label class='PumpSwitchLabel'>"."<input type='checkbox' class='PumpSwitch' id='".$row['Pin']."'>"."<span class='slider'>"."</span></label></td>";
					} else {
						echo "<td>"."<label class='PumpSwitchLabel'>"."<input type='checkbox' class='PumpSwitch' id='".$row['Pin']."' checked>"."<span class='slider'>"."</span></label></td>";
					}
					echo "</tr>";
				}
			}
			$con->close();
		?>

</body>
</html>