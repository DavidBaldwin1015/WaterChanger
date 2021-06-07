<?php
include('config.php');

$Command = $_POST['Command'];
$Pin = $_POST['Pin'];
$MultiplePumps = 0;

$con = mysqli_connect($host, $username, $password, $database);

if(!$con){
	die("Connection failed: ".mysqli_connect_error());
}

$Settings = mysqli_query($con, "SELECT Enabled FROM Settings WHERE Setting LIKE 'MultiplePumps'");
if($Settings){
	while($row = mysqli_fetch_assoc($Settings)){
		$MultiplePumps = $row['Enabled'];
	}
}



function PumpEnable($PinNum, $con, $pumps){
	$OnQuery = mysqli_query($con, "UPDATE Devices SET Status=1 WHERE Pin=".$PinNum);

	if($pumps == 0){
		$OffQuery = mysqli_query($con, "UPDATE Devices SET Status=0 WHERE Pin<>".$PinNum." AND DeviceType LIKE 'Pump'");
	}

	$Command = $PinNum+300;
	$Output = shell_exec("python3 ./SerialControl.py ".$Command);
	echo $Output;
}

function PumpOn(){
	$Command = 304;
	$Output=shell_exec("python3 ./SerialControl.py ".$Command);
	echo $Output;
}

function PumpOff(){
	$Command = 305;
	$Output=shell_exec("python3 ./SerialControl.py ".$Command);
	echo $Output;
}

switch($Command){
	case "PumpEn":
		PumpEnable($Pin, $con, $MultiplePumps);
		PumpOn();
		sleep(5);
		PumpOff();
		break;
}

$con->close();
?>