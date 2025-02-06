import React from "react";
import {
  Dimensions,
  SafeAreaView,
  StyleSheet,
  Text,
  TouchableOpacity,
  View,
} from "react-native";
import { LineChart } from "react-native-chart-kit";
import Icon from "react-native-vector-icons/MaterialIcons";

const MainPage = () => {
  const chartData = {
    labels: ["Sat", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri"],
    datasets: [
      {
        data: [80, 120, 90, 170, 140, 100, 150], // Sample data
        color: (opacity = 1) => `rgba(104, 58, 183, ${opacity})`, // Purple line
        strokeWidth: 2,
      },
    ],
  };

  const renderStatsCard = (
    title: string,
    value: string,
    subtitle: string,
    backgroundColor: string
  ) => (
    <View style={[styles.statsCard, { backgroundColor }]}>
      <Text style={styles.statsTitle}>{title}</Text>
      <Text style={styles.statsValue}>{value}</Text>
      <Text style={styles.statsSubtitle}>{subtitle}</Text>
    </View>
  );
  return (
    <SafeAreaView style={styles.container}>
      <View style={styles.content}>
        {/* Top bar */}
        <View style={styles.topBar}>
          <View style={styles.weatherInfo}>
            <Icon
              name="wb-sunny"
              size={24}
              color="#8b5cf6"
            />
            <View style={styles.weatherText}>
              <Text style={styles.temperature}>28°C</Text>
              <Text style={styles.weatherSubtext}>Today Weather</Text>
            </View>
          </View>
          <View style={styles.avatar} />
        </View>

        {/* Usage section */}
        <View style={styles.usageHeader}>
          <Text style={styles.sectionTitle}>Usage</Text>
          <TouchableOpacity>
            <Text style={styles.periodSelector}>Weekly ▼</Text>
          </TouchableOpacity>
        </View>
        {/* Chart */}
        <View style={{ padding: 10 }}>
          <LineChart
            data={chartData}
            width={Dimensions.get("window").width - 20}
            height={220}
            yAxisLabel="$"
            yAxisSuffix=""
            chartConfig={{
              backgroundGradientFrom: "#fff",
              backgroundGradientTo: "#fff",
              decimalPlaces: 0,
              color: (opacity = 1) => `rgba(104, 58, 183, ${opacity})`,
              labelColor: (opacity = 1) => `rgba(0, 0, 0, ${opacity})`,
              propsForDots: {
                r: "6",
                strokeWidth: "2",
                stroke: "#682EB7",
              },
            }}
            bezier
            style={{ borderRadius: 10 }}
          />
        </View>
        {/* Stats cards */}
        <View style={styles.statsContainer}>
          {renderStatsCard(
            "Electricity Cost",
            "$415.31",
            "This Week",
            "#8b5cf6"
          )}
          {renderStatsCard("Electricity Usage", "951.1", "kw", "#f97316")}
        </View>
        {/* Monthly average */}
        <View style={styles.monthlyAvg}>
          <Text style={styles.avgLabel}>Avg. Monthly</Text>
          <Text style={styles.avgValue}>12.520 kw</Text>
        </View>
      </View>
    </SafeAreaView>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: "#ffffff",
    paddingTop: 40,
  },
  content: {
    flex: 1,
    padding: 16,
  },
  topBar: {
    flexDirection: "row",
    justifyContent: "space-between",
    alignItems: "center",
  },
  weatherInfo: {
    flexDirection: "row",
    alignItems: "center",
  },
  weatherText: {
    marginLeft: 8,
  },
  temperature: {
    fontSize: 20,
    fontWeight: "bold",
  },
  weatherSubtext: {
    color: "#9ca3af",
  },
  avatar: {
    width: 40,
    height: 40,
    borderRadius: 20,
    backgroundColor: "#22c55e",
  },
  tabBar: {
    flexDirection: "row",
    marginTop: 20,
  },
  tab: {
    flex: 1,
    paddingVertical: 8,
    borderBottomWidth: 2,
    borderBottomColor: "transparent",
  },
  activeTab: {
    borderBottomColor: "#8b5cf6",
  },
  tabText: {
    textAlign: "center",
    color: "#9ca3af",
  },
  activeTabText: {
    color: "#8b5cf6",
    fontWeight: "bold",
  },
  usageHeader: {
    flexDirection: "row",
    justifyContent: "space-between",
    alignItems: "center",
    marginTop: 20,
  },
  sectionTitle: {
    fontSize: 18,
    fontWeight: "bold",
  },
  periodSelector: {
    color: "#9ca3af",
  },
  chart: {
    marginVertical: 8,
    borderRadius: 16,
  },
  statsContainer: {
    flexDirection: "row",
    marginTop: 20,
    gap: 16,
  },
  statsCard: {
    flex: 1,
    padding: 16,
    borderRadius: 16,
  },
  statsTitle: {
    color: "#ffffff",
    fontSize: 16,
  },
  statsValue: {
    color: "#ffffff",
    fontSize: 24,
    fontWeight: "bold",
    marginTop: 8,
  },
  statsSubtitle: {
    color: "rgba(255, 255, 255, 0.8)",
  },
  monthlyAvg: {
    flexDirection: "row",
    alignItems: "center",
    marginTop: 20,
  },
  avgLabel: {
    color: "#9ca3af",
  },
  avgValue: {
    fontSize: 18,
    fontWeight: "bold",
    marginLeft: 20,
  },
  bottomNav: {
    flexDirection: "row",
    justifyContent: "space-around",
    alignItems: "center",
    marginTop: "auto",
  },
  addButton: {
    padding: 12,
    backgroundColor: "#8b5cf6",
    borderRadius: 25,
  },
});

export default MainPage;
