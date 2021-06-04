<!DOCTYPE html>
<html>
<head>
	<meta name="viewport" content="width=device-width, inital-scale=1.0">
	<link rel="stylesheet" href="Styles.css">
</head>
<body>
	<ul id="NavMenu">
		<li><a href="index.php"><img src="monitor-outline.png" id="DashboardIcon"/><div class="tooltip"><span class="tooltiptext">Dashboard</span></div></a></li>
		<li><a href="Tanks.php"><div class="tooltip"><span class="tooltiptext">Tanks and Valves</span></div></a></li>
		<li><a href="Pumps.php"><div class="tooltip"><span class="tooltiptext">Pump Controls</span></div></a></li>
		<li><a href="Flows.php"><div class="tooltip"><span class="tooltiptext">Flowmeters</span></div></a></li>
		<li><a href="Manual.php"><div class="tooltip"><span class="tooltiptext">Manual Override</span></div></a></li>
	</ul><br>
	<div id="content">
	<a href="AddDevice.php">Add Device</a>
	<div id="SystemStatus">
		
		<?php

		?>
	</div>
</div>
</body>
</html>