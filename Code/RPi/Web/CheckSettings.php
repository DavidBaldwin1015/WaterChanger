<?php
include('config.php');

$Fetch = $_POST['Fetch'];

$con = mysqli_connect($host, $username, $password, $database);

if(!$con){
	die("Connection failed: ".mysqli_connect_error());
}

if($Fetch == "All"){
	$Settings = mysqli_query($con, "SELECT Setting, Enabled FROM Settings");
	if($Settings){
		while($row = mysqli_fetch_assoc($Settings)){
			$Setting = $row['Setting'];
			$Enabled = $row['Enabled'];
			$Settings_array[] = array("Setting"=> $Setting, "Enabled" => $Enabled);
		}
		echo json_encode($Settings_array);
	}
}

$con -> close();
?>