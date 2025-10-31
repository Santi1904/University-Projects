// Dependencies
import { StyleSheet, View, Text, Image } from 'react-native';

// Styles and Components
import { Colors } from '../styles';
import Button from '../components/Button';
import BackButton from '../components/backButton';


export default function Premium() {
  return (
    <View style={styles.container}>
      <BackButton />

      <View style={styles.headerContainer}>
        <Image source={require('../../assets/premium.png')} style={styles.image}/>
        <Text style={styles.title}>BraGuia Premium</Text>
        <Text style={styles.description}>
          Transforme a sua viagem numa aventura única!
        </Text>
        <Text style={styles.subDescription}>
          Atualize agora para a versão premium e tenha acesso a todas as funcionalidades exclusivas.
        </Text>
      </View>

      <View style={styles.tableContainer}>
        <View style={styles.rowContainer}>
          <Text style={styles.smallTitle}>Vantagens</Text>
          <Text style={styles.smallTitle}>Descrição</Text>
        </View>
        <View style={styles.rowContainer}>
          <Text style={styles.rowText}>Capacidade de navegação</Text>
          <Text style={styles.rowText}>Acesso completo a todos os recursos de navegação, incluíndo navegação offline</Text>
        </View>
        <View style={styles.rowContainer}>
          <Text style={styles.rowText}>Consulta de mídia</Text>
          <Text style={styles.rowText}>Visualização imediata de fotos e vídeos dos diferentes destinos</Text>
        </View>
        <View style={styles.rowContainer}>
          <Text style={styles.rowText}>Experiência sem publicidade</Text>
          <Text style={styles.rowText}>Explore sem a interrupeção de anúncios</Text>
        </View>
      </View>

      <View style={styles.upgradeButton}>
        <Button title="Experimentar agora" onPress={null} />
      </View>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: Colors.white,
    justifyContent: 'space-between',
    paddingHorizontal: 16,
  },
  headerContainer: {
    alignItems: 'center',
    marginVertical: 50,
  },
  image: {
    width: 100,
    height: 100,
    marginBottom: 16,
  },
  title: {
    fontSize: 28,
    color: Colors.black,
    fontWeight: 'bold',
    marginBottom: 16,
  },
  description: {
    fontSize: 16,
    color: Colors.gray500,
    marginBottom: 8,
  },
  subDescription: {
    fontSize: 16,
    color: Colors.gray500,
  },
  tableContainer: {
    flex: 1,
  },
  rowContainer: {
    flexDirection: 'row',
    justifyContent: 'space-between',
    paddingHorizontal: 16,
    paddingVertical: 6,
  },
  smallTitle: {
    fontSize: 18,
    color: Colors.black,
    fontWeight: 'bold',
    marginBottom: 8,
    width: '50%',
  },
  rowText: {
    width: '50%',
    fontSize: 14,
    color: Colors.gray500,
  },
  upgradeButton: {
    marginVertical: 30,
    marginHorizontal: 16,
  }
});
