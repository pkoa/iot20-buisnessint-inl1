using System;
using System.IO;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Extensions.Http;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Logging;
using Newtonsoft.Json;
using System.Collections.Generic;

namespace Azurefunction
{
    public static class GetFromCosmosdb
    {
        [FunctionName("GetFromCosmosdb")]
        public static async Task<IActionResult> Run(
            [HttpTrigger(AuthorizationLevel.Function, "get", Route = null)] HttpRequest req,
            [CosmosDB(databaseName:"IoT20", collectionName:"Messages", ConnectionStringSetting = "CosmosDb", 
            CreateIfNotExists = true, SqlQuery ="SELECT * FROM c")]IEnumerable<dynamic> cosmosdb,
            ILogger log)
        {
            if(cosmosdb == null)
            {
                log.LogInformation($"Requested items not found");
                return new NotFoundResult();
            }

            log.LogInformation($"Requested items found");
            return new OkObjectResult(cosmosdb);
        }
    }
}
