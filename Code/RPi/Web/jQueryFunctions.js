 $(document).ready(function(){
    $("#DeviceTypeSelect").on("change", function(){

        var selected = $(this).val()

        if(selected == "Valve" || selected == "Tank" || selected == "Pump"){

            $("#Digital").prop("checked", true);
            $("#Output").prop("checked", true);

            $.ajax({
                type:"POST",
                url:"PinChecks.php",
                data: {PinType: "Digital"},
                dataType: "json",
                success: function(response){

                    var len = response.length;
                    console.log(len);

                    for(var i = 0; i < len; i++){
                        var id = response[i]["PinNum"];


                        $("#Pins").append($("<option>", {"value": id, "text": id}));
                    }
                }
            })
        }
    })

}); 