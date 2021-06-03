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
if($sql->execute()===TRUE){
	echo json_encode(array("Status"=>1));
} else {
	echo json_encode(array("Status"=>2))
}

$con->close();
?>