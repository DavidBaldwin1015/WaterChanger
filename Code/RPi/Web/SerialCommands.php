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

switch($Command){
	case "PumpEn":
		PumpEnable($Pin, $con, $MultiplePumps);
		PumpOn();
		sleep(5);
		PumpOff();
		break;
}

function PumpEnable($PinNum, $con, $pumps){
	$OnQuery = mysqli_query($con, "UPDATE Devices SET Status=1 WHERE Pin==".$PinNum);

	if($pumps == 0){
		$OffQuery = mysqli_query($con, "UPDATE Devices SET Status=0 WHERE Pin!=".$PinNum." AND DeviceType LIKE 'Pump'");
	}

	$Command = $PinNum+300;
	exec("python3 ./SerialControl.py ".$Command);

}

function PumpOn(){
	$Command = 304;
	exec("python3 ./SerialControl.py ".$Command);
}

function PumpOff(){
	$Command = 305;
	exec("python3 ./SerialControl.py ".$Command);
}

$con->close();
?>