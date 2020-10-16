import React, { useState } from 'react';
import { StyleSheet, Text, View, Animated, TouchableOpacity, Alert } from 'react-native';
import { MaterialCommunityIcons } from '@expo/vector-icons';
import { AntDesign } from '@expo/vector-icons';
import { Ionicons } from '@expo/vector-icons';
import { FontAwesome5 } from '@expo/vector-icons';

export default function App() {

  const [scoreCount, setscoreCount] = useState(0);
  const [status, setStatus] = useState('Escolha uma das caixas');
  const [clicks, setClicks] = useState(0);

  const [iconRotation] = useState(new Animated.Value(0));

  const onButtonPress = () => {
    setClicks(clicks+1);
    Animated.timing(iconRotation, {
      toValue: 50 * scoreCount,
      duration: 700,
      useNativeDriver: true,
    }).start();

    let id = Math.floor(Math.random() * (3 - 1) + 1)
    if (id === Math.floor(Math.random() * (4 - 1) + 1)) {
      setscoreCount(scoreCount + 1)
      setStatus("Você encontrou o doce!");
      if (scoreCount > 10) {
        Alert.alert('Você venceu!')
        setscoreCount(0);
        setClicks(0);
      }
      return;
    }
    setStatus("Tente novamente");

  }
  const getIcon = () => {
    if (scoreCount > 2) return (<Ionicons name="md-happy" size={24} color="black" />)
    return (<AntDesign name="meh" size={24} color="black" />)
  }


  return (
    <View style={styles.container}>
      <MaterialCommunityIcons name="sunglasses" size={50} color="black" style={{ marginBottom: 50 }} />

      <View style={styles.header}>

        <Text style={{ marginRight: 20 }}>Score {scoreCount * 10}</Text>
        {getIcon()}
      </View>
      <Text>Tentativas {clicks}</Text>

      <View style={styles.buttonContainer}>
        <TouchableOpacity style={styles.button} onPress={() => onButtonPress()} >
          <Animated.View
            style={{
              transform: [
                {
                  rotate: iconRotation.interpolate({
                    inputRange: [0, 90],
                    outputRange: ['0deg', '-90deg'],
                  }),
                },
              ],
            }}>
            <FontAwesome5 name="candy-cane" size={24} color="black" />
          </Animated.View>
        </TouchableOpacity>

        <TouchableOpacity style={styles.button} onPress={() => onButtonPress()} >
          <Animated.View
            style={{
              transform: [
                {
                  rotate: iconRotation.interpolate({
                    inputRange: [0, 90],
                    outputRange: ['0deg', '-90deg'],
                  }),
                },
              ],
            }}>
            <FontAwesome5 name="candy-cane" size={24} color="black" />
          </Animated.View>
        </TouchableOpacity>
        {scoreCount > 4 &&
          <>
            <TouchableOpacity style={styles.button} onPress={() => onButtonPress()} >
              <Animated.View
                style={{
                  transform: [
                    {
                      rotate: iconRotation.interpolate({
                        inputRange: [0, 90],
                        outputRange: ['0deg', '-90deg'],
                      }),
                    },
                  ],
                }}>
                <FontAwesome5 name="candy-cane" size={24} color="black" />
              </Animated.View>
            </TouchableOpacity>
            <TouchableOpacity style={styles.button} onPress={() => onButtonPress()} >
              <Animated.View
                style={{
                  transform: [
                    {
                      rotate: iconRotation.interpolate({
                        inputRange: [0, 90],
                        outputRange: ['0deg', '-90deg'],
                      }),
                    },
                  ],
                }}>
                <FontAwesome5 name="candy-cane" size={24} color="black" />
              </Animated.View>
            </TouchableOpacity>
          </>
        }

      </View>
      {
        status === "Você encontrou o doce!" ? <Text style={styles.statusSucess}>{status}</Text> : <Text style={styles.statusFail}>{status}</Text>

      }
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#ffe',
    alignItems: 'center',
    justifyContent: 'center',
  },
  button: {
    padding: 30,
    borderRadius: 5,
    elevation: 2,
    margin: 10,
  },
  header: {
    flexDirection: "row",
    fontSize: 10,
    marginBottom: 30
  },
  buttonContainer: {
    flexDirection: "row",
  },
  statusSucess: {
    marginTop: 15,
    color: 'green'
  },
  statusFail: {
    marginTop: 15,
    color: 'red'
  }
});
