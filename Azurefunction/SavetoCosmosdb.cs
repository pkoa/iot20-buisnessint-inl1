using IoTHubTrigger = Microsoft.Azure.WebJobs.EventHubTriggerAttribute;

using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Host;
using Microsoft.Azure.EventHubs;
using System.Text;
using System.Net.Http;
using Microsoft.Extensions.Logging;

namespace Azurefunction
{
    public static class SavetoCosmosdb
    {
        private static HttpClient client = new HttpClient();

        [FunctionName("SavetoCosmosdb")]
        public static void Run([IoTHubTrigger("messages/events", Connection = "IotHubConn", ConsumerGroup = "$Default")] EventData message,
            [CosmosDB(databaseName: "dbmaster", collectionName: "Messages", ConnectionStringSetting = "CosmosDb", CreateIfNotExists = true)] out dynamic cosmos,
        ILogger log)
        {
            log.LogInformation($"Message/events: {Encoding.UTF8.GetString(message.Body.Array)}");

            cosmos = Encoding.UTF8.GetString(message.Body.Array);
        }

    }
}