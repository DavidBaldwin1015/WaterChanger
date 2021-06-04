<?php
include('config.php');

$Name = $_POST['DevName'];
$Type = $_POST['DevType'];
$AD = $_POST['AD'];
$IO = $_POST['InOut'];
$Pin = $_POST['Pin'];
$InitStat = $_POST['Stat'];

$con = mysqli_connect($host, $username, $password, $database);

if(!$con){
	die("Connection failed: ".mysqli_connect_error());
}


//Clean up the inputs so the database can take them
if($AD == "Digital"){
	$ADClean = "D";
} else {
	$ADClean = "A";
}

if($IO == "Output"){
	$IOClean = "O";
} else {
	$IOClean = "I";
}

if($IniStat == "On"){
	$StatClean = 1;
} else {
	$StatClean = 0;
}


$sql = "INSERT INTO Devices (DeviceName, DeviceType, Active, IO, Status, Pin, AD) VALUES ('".$Name."', '".$Type."', 1, '".$IOClean."', '".$StatClean."', ".$Pin.", '".$ADClean."')";
if($con->query($sql)==TRUE){
	//Confirm the new record is there
	$result = mysqli_query($con, "SELECT idDevices FROM Devices WHERE DeviceName LIKE ".$Name." AND Pin LIKE ".$Pin);
	if(mysqli_num_rows($result) == 0){
		echo json_encode(array("Status"=>2));
	} else {
		echo json_encode(array("Status"=>1));
	}
} else {
	echo json_encode(array("Status"=>3));
}


$PinUpdate = $con->prepare("UPDATE Pins SET Used=1, PinDir=? WHERE PinNum=? AND PinType=?");
$PinUpdate->bind_param("sis", $IOClean, $Pin, $ADClean);
$PinUpdate->execute();

//Add code to mark pin in Pins table as used

$con->close();
?>