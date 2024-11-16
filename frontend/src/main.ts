import './app.scss'
import App from './App.svelte'
import { DemoApiService } from './services/demoApiService';
import { FritzGateApiService } from './services/fritzGateApiService';

const isDemo = window.location.hostname.endsWith(".github.io");
const baseUrl = isDemo ? "/FritzGate" : ""
const apiService = isDemo
  ? new DemoApiService(baseUrl)
  : new FritzGateApiService()
const app = new App({
  target: document.getElementById('app')!,
  props: {
    api: apiService,
    baseUrl: baseUrl,
  }
});

export default app
