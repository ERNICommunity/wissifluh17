using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Migrations;
using System;
using System.Collections.Generic;

namespace PMS.Backend.Data.Migrations
{
    public partial class InitialCreate : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "SensorNode",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "uniqueidentifier", nullable: false),
                    Latitude = table.Column<double>(type: "float", nullable: false),
                    Longitude = table.Column<double>(type: "float", nullable: false),
                    Name = table.Column<string>(type: "nvarchar(max)", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_SensorNode", x => x.Id);
                });

            migrationBuilder.CreateTable(
                name: "SensorNodeData",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:ValueGenerationStrategy", SqlServerValueGenerationStrategy.IdentityColumn),
                    DateTime = table.Column<DateTime>(type: "datetime2", nullable: false),
                    Humidity = table.Column<double>(type: "float", nullable: false),
                    Pm10 = table.Column<double>(type: "float", nullable: false),
                    Pm2_5 = table.Column<double>(type: "float", nullable: false),
                    SensorNodeId = table.Column<Guid>(type: "uniqueidentifier", nullable: false),
                    Temperature = table.Column<double>(type: "float", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_SensorNodeData", x => x.Id);
                    table.ForeignKey(
                        name: "FK_SensorNodeData_SensorNode_SensorNodeId",
                        column: x => x.SensorNodeId,
                        principalTable: "SensorNode",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateIndex(
                name: "IX_SensorNodeData_SensorNodeId",
                table: "SensorNodeData",
                column: "SensorNodeId");
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "SensorNodeData");

            migrationBuilder.DropTable(
                name: "SensorNode");
        }
    }
}
