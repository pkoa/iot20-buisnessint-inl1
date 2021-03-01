using IoTHubTrigger = Microsoft.Azure.WebJobs.EventHubTriggerAttribute;

using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Host;
using Microsoft.Azure.EventHubs;
using System.Text;
using System.Net.Http;
using Microsoft.Extensions.Logging;
using System.Data.SqlClient;
using System;
using Newtonsoft.Json;
using Savetosql.Models;

namespace Savetosql
{
    public static class SavetoSql
    {
        private static HttpClient client = new HttpClient();

        [FunctionName("SavetoSql")]
        public static void Run([IoTHubTrigger("messages/events", Connection = "IothubConn")] EventData message, ILogger log)
        {
            log.LogInformation($"Payload: {Encoding.UTF8.GetString(message.Body.Array)}");

            DeviceMessage msg = JsonConvert.DeserializeObject<DeviceMessage>(Encoding.UTF8.GetString(message.Body.Array));
            using (SqlConnection conn = new SqlConnection(Environment.GetEnvironmentVariable("sqldb")))
            {
                string query = "INSERT INTO DeviceMessages VALUES(@DeviceId, @Temperature, @Humidity, @Formatted_Time)";

                conn.Open();
                using (SqlCommand cmd = new SqlCommand(query, conn))
                {
                    cmd.Parameters.AddWithValue("@DeviceId", msg.DeviceId);
                    cmd.Parameters.AddWithValue("@Temperature", msg.Temperature);
                    cmd.Parameters.AddWithValue("@Humidity", msg.Humidity);
                    cmd.Parameters.AddWithValue("@Formatted_Time", msg.Formatted_Time);

                    cmd.ExecuteNonQuery();
                }
            }
        }
    }
}