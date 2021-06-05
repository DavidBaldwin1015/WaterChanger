<!DOCTYPE html>
<html>
<head>
	<meta name="viewport" content="width=device-width, inital-scale=1.0">
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
	<script src="jQueryFunctions.js"></script>
	<link rel="stylesheet" href="Styles.css">
</head>
<body>
	<ul id="NavMenu">
		<li><a href="index.php"><img src="monitor-outline.png" id="Icon"/><!-- <div class="tooltip"><span class="tooltiptext">Dashboard</span></div> --></a></li>
		<li><a href="Tanks.php"><img src="valve.png" id="Icon"/><!-- <div class="tooltip"><span class="tooltiptext">Tanks and Valves</span></div> -->Tanks and Valves</a></li>
		<li><a href="Pumps.php"><img src="water-pump.png" id="Icon"/><!-- <div class="tooltip"><span class="tooltiptext">Pump Controls</span></div> -->Pumps</a></li>
		<li><a href="Flows.php"><img src="humidity.png" id="Icon"/><!-- <div class="tooltip"><span class="tooltiptext">Flowmeters</span></div> -->Sensors</a></li>
		<!-- <li><a href="Manual.php"><div class="tooltip"><span class="tooltiptext">Manual Override</span></div> Manual Override</a></li> -->
		<li><a href="Admin.php"><img src="double-wrench-outline.png" id="Icon"/> Administration </a></li>
	</ul><br>
	<div id="content">
	<a href="AddDevice.php">Add Device</a>
	<div id="SystemStatus">
		<?php
			include('config.php');
			$con = mysqli_connect($host, $username, $password, $database);

			if(!$con){
				die("Connection failed: ".mysqli_connect_error());
			}

			$test = mysqli_query($con, "SELECT ErrorType, ErrorExp, ErrorSrc FROM Errors WHERE Resolved == 0");
			if(!$test || mysqli_num_rows($test)==0){
				echo "<div class='NoErrors'>";
				echo "<span class='exit' onclick='this.parentElement.style.display='none';'>&times;</span>";
				echo "No errors. All systems functioning.";
				echo "</div>";				
			} else {				
				while($row = mysqli_fetch_assoc($test)){
					echo "<div class='Error'>";
					echo "<span class='exit' onclick='this.parentElement.style.display='none';'>&times;</span>";
					echo "Error ".$row['ErrorType'].": ".$row['ErrorExp']." from ".$row['ErrorSrc'].".";
					echo "</div>";
				}
			}
			$con -> close();
		?>
	</div>

</div>
</body>
<foot>
	<p> All icons courtesy of Freepik. </p>
</foot>
</html>