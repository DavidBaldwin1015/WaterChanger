<?php

$PinType = $_POST['PinType'];

$con = mysqli_connect("127.0.0.1", "FormUser", "Plankt0n!", "WaterControls");

if(mysqli_connect_errno()){
	echo "Failed to connect to MySQL: " . mysqli_connect_error();
}

if($PinType == "Digital"){
	$result = mysqli_query($con, "SELECT PinNum FROM Pins WHERE Pintype LIKE 'D' AND Used LIKE 0");
	if(mysqli_num_rows($result) > 0){
        while($row = mysqli_fetch_assoc($result)){
                echo json_encode($row);
		}
	} else {
                echo json_encode("0");
	}

} else {
	echo json_encode("Error 2");
}
?> 