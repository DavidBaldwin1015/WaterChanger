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
                    for(var i = 0; i < len; i++){
                        $("#Pins").append($("<option>", {"value": response[i].PinNum, "text": response[i].PinNum})).insertAfter($(this));
                    }
                }
            })
        }
    })

}); 