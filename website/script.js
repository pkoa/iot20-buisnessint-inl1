/* script file */
let tabledata = document.getElementById('tabledata')

fetch("https://cosmosdb-iot20-save-get.azurewebsites.net/api/GetFromCosmosdb?code=oMXAifKJkaXdKftp7rBnvlwQTmzWWrsupNTHstcgI9qJlMJi30Y04w==")
.then(res => res.json())
.then(data =>{
    for(let row of data){
        tabledata.innerHTML += `<tr class="table-dark"><td>${row.id}</td><td>${row.deviceid}</td><td>${row.temperature}</td><td>${row.humidity}</td><td>${row.halleffect}</td><td>${row.formatted_time}</td>`
    }
})