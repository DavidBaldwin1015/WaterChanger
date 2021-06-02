<? php

$json = file_get_contents('php://input');

$data = json_decode($json);

$con = mysqli_connect("127.0.0.1", "FormUser", "Plankt0n!", "WaterControls");

if(mysqli_connect_errno()){
	echo "Failed to connect to MySQL: " . mysqli_connect_error();
}

if($data -> PinType == "Digital"){
	$result = mysqli_query($con, "SELECT PinNum FROM Pins WHERE Pintype == 'D' AND Used == 0");
	if($result){
		echo json_encode(array("PinNum" => $result["PinNum"]))
	}
}
?>