<? php

$json = file_get_contents('php://input');

$data = json_decode($json);
$PinType = $data->PinType;

$con = mysqli_connect("127.0.0.1", "FormUser", "Plankt0n!", "WaterControls");

if(mysqli_connect_errno()){
	echo "Failed to connect to MySQL: " . mysqli_connect_error();
}

if($PinType == "Digital"){
	$result = mysqli_query($con, "SELECT PinNum FROM Pins WHERE Pintype LIKE 'D' AND Used LIKE 0");
	$output = $result->fetch_all(MYSQLI_ASSOC);
	echo json_encode($output);
	}
?>