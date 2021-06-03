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

$sql = $con->prepare("INSERT INTO Devices (idDevices, DeviceName, DeviceType, Active, IO, Status, Pin, AD) VALUES (null, ?, ?, 1, ?, ?, ?, ?)");
$sql->bind_param("ssssis", $Name, $Type, $IO, $InitStat, $Pin, $AD);
$sql->execute();

//Confirm the new record is there
$result = mysqli_query($con, "SELECT idDevices FROM Devices WHERE DeviceName LIKE ".$Name." AND Pin LIKE ".$Pin);
if(mysqli_num_rows($result) == 0){
	echo json_encode(array("Status":2));
} else {
	echo json_encode(array("Status":1));
}

//Add code to mark pin in Pins table as used

$con->close();
?>