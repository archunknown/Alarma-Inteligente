#ifndef INDEX_H
#define INDEX_H

const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Control Web - Colegio Raúl Porras Barrenechea</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
            color: #333;
        }
        
        .container {
            max-width: 1200px;
            margin: 0 auto;
            padding: 20px;
        }
        
        .header {
            text-align: center;
            background: rgba(255, 255, 255, 0.1);
            backdrop-filter: blur(10px);
            border-radius: 20px;
            padding: 30px;
            margin-bottom: 30px;
            border: 1px solid rgba(255, 255, 255, 0.2);
            box-shadow: 0 8px 32px rgba(0, 0, 0, 0.1);
        }
        
        .header h1 {
            color: white;
            font-size: 2.5rem;
            margin-bottom: 10px;
            text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.3);
        }
        
        .header p {
            color: rgba(255, 255, 255, 0.9);
            font-size: 1.2rem;
        }
        
        .status-bar {
            background: rgba(255, 255, 255, 0.95);
            border-radius: 10px;
            padding: 15px;
            margin-bottom: 20px;
            text-align: center;
            font-weight: bold;
            font-size: 1.1rem;
        }
        
        .status-none { background: rgba(128, 128, 128, 0.2); }
        .status-security { background: rgba(255, 107, 107, 0.2); color: #c62828; }
        .status-classes { background: rgba(76, 175, 80, 0.2); color: #2e7d32; }
        
        .main-controls {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
            gap: 20px;
            margin-bottom: 30px;
        }
        
        .control-card {
            background: rgba(255, 255, 255, 0.95);
            border-radius: 15px;
            padding: 25px;
            text-align: center;
            box-shadow: 0 10px 30px rgba(0, 0, 0, 0.2);
            transition: all 0.3s ease;
            border: 2px solid transparent;
        }
        
        .control-card:hover {
            transform: translateY(-5px);
            box-shadow: 0 15px 40px rgba(0, 0, 0, 0.3);
        }
        
        .control-card.active {
            border-color: #4CAF50;
            background: rgba(76, 175, 80, 0.1);
        }
        
        .control-card.disabled {
            opacity: 0.5;
            pointer-events: none;
        }
        
        .btn {
            background: linear-gradient(45deg, #667eea, #764ba2);
            color: white;
            border: none;
            padding: 15px 30px;
            border-radius: 10px;
            font-size: 1.1rem;
            font-weight: bold;
            cursor: pointer;
            transition: all 0.3s ease;
            width: 100%;
            margin: 10px 0;
            box-shadow: 0 4px 15px rgba(0, 0, 0, 0.2);
        }
        
        .btn:hover {
            transform: translateY(-2px);
            box-shadow: 0 6px 20px rgba(0, 0, 0, 0.3);
        }
        
        .btn:disabled {
            opacity: 0.5;
            cursor: not-allowed;
            transform: none;
        }
        
        .btn.danger {
            background: linear-gradient(45deg, #ff6b6b, #ee5a52);
        }
        
        .btn.success {
            background: linear-gradient(45deg, #4CAF50, #45a049);
        }
        
        .btn.warning {
            background: linear-gradient(45deg, #ff9800, #f57c00);
        }
        
        .mode-panel {
            background: rgba(255, 255, 255, 0.95);
            border-radius: 15px;
            padding: 30px;
            margin-top: 20px;
            box-shadow: 0 10px 30px rgba(0, 0, 0, 0.2);
            display: none;
        }
        
        .mode-panel.active {
            display: block;
            animation: fadeIn 0.5s ease;
        }
        
        @keyframes fadeIn {
            from { opacity: 0; transform: translateY(20px); }
            to { opacity: 1; transform: translateY(0); }
        }
        
        .panel-header {
            text-align: center;
            margin-bottom: 25px;
            padding-bottom: 15px;
            border-bottom: 2px solid #eee;
        }
        
        .panel-header h2 {
            color: #333;
            font-size: 1.8rem;
            margin-bottom: 10px;
        }
        
        .status-indicator {
            display: inline-block;
            width: 12px;
            height: 12px;
            border-radius: 50%;
            margin-right: 8px;
        }
        
        .status-active {
            background: #4CAF50;
            box-shadow: 0 0 10px rgba(76, 175, 80, 0.5);
        }
        
        .feature-grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
            gap: 15px;
            margin-top: 20px;
        }
        
        .feature-card {
            background: rgba(255, 255, 255, 0.7);
            border-radius: 10px;
            padding: 20px;
            text-align: center;
            border: 1px solid #eee;
            transition: all 0.3s ease;
        }
        
        .feature-card:hover {
            background: rgba(255, 255, 255, 0.9);
            transform: translateY(-3px);
        }
        
        .time-config {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
            gap: 15px;
            margin: 20px 0;
        }
        
        .time-input {
            background: rgba(255, 255, 255, 0.9);
            border: 2px solid #ddd;
            border-radius: 8px;
            padding: 15px;
        }
        
        .time-input label {
            display: block;
            font-weight: bold;
            margin-bottom: 5px;
            color: #333;
        }
        
        .time-input input {
            width: 100%;
            padding: 8px;
            border: 1px solid #ddd;
            border-radius: 5px;
            font-size: 1rem;
        }
        
        .emergency-alert {
            background: linear-gradient(45deg, #ff4757, #ff3838);
            color: white;
            padding: 20px;
            border-radius: 10px;
            text-align: center;
            margin: 20px 0;
            box-shadow: 0 4px 15px rgba(255, 71, 87, 0.3);
        }
        
        .log-panel {
            background: rgba(0, 0, 0, 0.8);
            color: #00ff00;
            padding: 20px;
            border-radius: 10px;
            margin-top: 20px;
            font-family: 'Courier New', monospace;
            font-size: 0.9rem;
            max-height: 300px;
            overflow-y: auto;
        }
        
        .sensor-grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(150px, 1fr));
            gap: 15px;
            margin-top: 20px;
        }
        
        .sensor-item {
            background: rgba(255, 255, 255, 0.8);
            padding: 15px;
            border-radius: 8px;
            text-align: center;
        }
        
        .sensor-name {
            font-weight: bold;
            margin-bottom: 5px;
        }
        
        .sensor-status {
            padding: 5px 10px;
            border-radius: 15px;
            font-size: 0.9rem;
            font-weight: bold;
        }
        
        .sensor-active {
            background: #4CAF50;
            color: white;
        }
        
        .sensor-standby {
            background: #ff9800;
            color: white;
        }
        
        .sensor-off {
            background: #ccc;
            color: #666;
        }
    </style>
</head>
<body>
    <div class="container">
        <!-- Header -->
        <div class="header">
            <h1>🏫 Control Web</h1>
            <p>Colegio Raúl Porras Barrenechea</p>
        </div>
        
        <!-- Status Bar -->
        <div class="status-bar" id="statusBar">
            <span id="statusText">Sistema Iniciado - Selecciona un modo</span>
        </div>
        
        <!-- Main Controls -->
        <div class="main-controls">
            <div class="control-card" id="modeClases">
                <h3>📚 Modo Clases</h3>
                <p>Control de horarios y actividades académicas</p>
                <button class="btn" id="btnClases" onclick="setMode('classes')">Activar Modo Clases</button>
            </div>
            
            <div class="control-card" id="modeVigilancia">
                <h3>🔒 Modo Seguridad</h3>
                <p>Sistema de seguridad y monitoreo PIR</p>
                <button class="btn" id="btnSeguridad" onclick="setMode('security')">Activar Modo Seguridad</button>
            </div>
            
            <div class="control-card">
                <h3>🔇 Control de Sonido</h3>
                <p>Detener todas las alertas sonoras</p>
                <button class="btn danger" onclick="stopBuzzer()">Detener Buzzer</button>
            </div>
        </div>
        
        <!-- Panel Modo Clases -->
        <div class="mode-panel" id="panelClases">
            <div class="panel-header">
                <h2><span class="status-indicator status-active"></span>Modo Clases Activo</h2>
                <p>Gestión de horarios y actividades académicas</p>
            </div>
            
            <div class="feature-grid">
                <div class="feature-card">
                    <h3>⏰ Configurar Horarios</h3>
                    <p>Establece los horarios para timbres automáticos</p>
                    <button class="btn" onclick="toggleConfig('configHorarios')">Configurar</button>
                </div>
                
                <div class="feature-card">
                    <h3>🚨 Alarma de Emergencia</h3>
                    <p>Activar/desactivar alarma manual</p>
                    <button class="btn warning" id="emergencyBtn" onclick="toggleEmergency()">Activar Alarma</button>
                </div>
            </div>
            
            <!-- Configuración de Horarios -->
            <div id="configHorarios" style="display: none; margin-top: 30px;">
                <h3>⏰ Configuración de Horarios</h3>
                <div class="time-config">
                    <div class="time-input">
                        <label>Timbre de Entrada:</label>
                        <input type="time" id="entrada" value="07:30">
                    </div>
                    <div class="time-input">
                        <label>Timbre de Receso:</label>
                        <input type="time" id="receso" value="10:30">
                    </div>
                    <div class="time-input">
                        <label>Timbre de Salida:</label>
                        <input type="time" id="salida" value="12:30">
                    </div>
                </div>
                <button class="btn success" onclick="saveHorarios()">Guardar Horarios</button>
                <p><strong>Hora actual del sistema:</strong> <span id="currentTime">--:--</span></p>
            </div>
            <div style="text-align: center; margin-top: 20px;">
                <button class="btn danger" onclick="setMode('none')">Desactivar Clases</button>
            </div>
        </div>
        
        <!-- Panel Modo Seguridad -->
        <div class="mode-panel" id="panelSeguridad">
            <div class="panel-header">
                <h2><span class="status-indicator status-active"></span>Modo Seguridad Activo</h2>
                <p>Sistema de detección PIR y alarma automática</p>
            </div>
            
            <div class="sensor-grid">
                <div class="sensor-item">
                    <div class="sensor-name">Sensor PIR</div>
                    <div class="sensor-status sensor-active" id="pirStatus">MONITOREANDO</div>
                </div>
                <div class="sensor-item">
                    <div class="sensor-name">LED Indicador</div>
                    <div class="sensor-status sensor-standby" id="ledStatus">EN ESPERA</div>
                </div>
                <div class="sensor-item">
                    <div class="sensor-name">Buzzer</div>
                    <div class="sensor-status sensor-standby" id="buzzerStatus">EN ESPERA</div>
                </div>
                <div class="sensor-item">
                    <div class="sensor-name">Conexión WiFi</div>
                    <div class="sensor-status sensor-active">CONECTADO</div>
                </div>
            </div>
            
            <div style="text-align: center; margin-top: 20px;">
                <button class="btn danger" onclick="setMode('none')">Desactivar Seguridad</button>
            </div>
        </div>
        
        <!-- Log Panel -->
        <div class="log-panel" id="logPanel">
            <div id="logContent">Cargando registro del sistema...</div>
        </div>
    </div>
    
    <script>
        let currentMode = 'none';
        let emergencyActive = false;
        let updateInterval;
        
        // Inicializar
        document.addEventListener('DOMContentLoaded', function() {
            updateStatus();
            updateTime();
            updateInterval = setInterval(updateStatus, 2000);
            setInterval(updateTime, 1000);
        });
        
        async function setMode(mode) {
            try {
                const response = await fetch('/api/mode', {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify({ mode: mode })
                });
                
                if (response.ok) {
                    currentMode = mode;
                    updateUI();
                    updateStatus();
                } else {
                    alert('Error al cambiar modo');
                }
            } catch (error) {
                console.error('Error:', error);
                alert('Error de conexión');
            }
        }
        
        async function toggleEmergency() {
            try {
                const response = await fetch('/api/emergency', {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify({ active: !emergencyActive })
                });
                
                if (response.ok) {
                    emergencyActive = !emergencyActive;
                    updateEmergencyButton();
                }
            } catch (error) {
                console.error('Error:', error);
            }
        }
        
        async function stopBuzzer() {
            try {
                const response = await fetch('/api/stop-buzzer', {
                    method: 'POST'
                });
                
                if (response.ok) {
                    alert('🔇 Buzzer detenido');
                }
            } catch (error) {
                console.error('Error:', error);
            }
        }
        
        async function saveHorarios() {
            const entrada = document.getElementById('entrada').value;
            const receso = document.getElementById('receso').value;
            const salida = document.getElementById('salida').value;
            
            try {
                const response = await fetch('/api/horarios', {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify({ entrada, receso, salida })
                });
                
                if (response.ok) {
                    alert(`Horarios guardados:\n• Entrada: ${entrada}\n• Receso: ${receso}\n• Salida: ${salida}`);
                }
            } catch (error) {
                console.error('Error:', error);
            }
        }
        
        function toggleConfig(id) {
            const element = document.getElementById(id);
            element.style.display = element.style.display === 'none' ? 'block' : 'none';
        }
        
        async function updateStatus() {
            try {
                const response = await fetch('/api/status');
                const data = await response.json();
                
                currentMode = data.mode;
                emergencyActive = data.emergencyActive;
                
                updateUI();
                updateSensorStatus(data);
                updateLog();
                
            } catch (error) {
                console.error('Error updating status:', error);
            }
        }
        
        function updateUI() {
            // Reset all cards
            document.querySelectorAll('.control-card').forEach(card => {
                card.classList.remove('active', 'disabled');
            });
            
            document.querySelectorAll('.mode-panel').forEach(panel => {
                panel.classList.remove('active');
            });
            
            // Update status bar
            const statusBar = document.getElementById('statusBar');
            const statusText = document.getElementById('statusText');
            
            statusBar.className = 'status-bar status-' + currentMode;
            
            switch(currentMode) {
                case 'security':
                    statusText.textContent = '🔒 MODO SEGURIDAD ACTIVO - Monitoreando PIR';
                    document.getElementById('modeVigilancia').classList.add('active');
                    document.getElementById('modeClases').classList.add('disabled');
                    document.getElementById('panelSeguridad').classList.add('active');
                    break;
                case 'classes':
                    statusText.textContent = '📚 MODO CLASES ACTIVO - Horarios y emergencias';
                    document.getElementById('modeClases').classList.add('active');
                    document.getElementById('modeVigilancia').classList.add('disabled');
                    document.getElementById('panelClases').classList.add('active');
                    break;
                default:
                    statusText.textContent = 'Sistema en espera - Selecciona un modo';
                    break;
            }
            
            updateEmergencyButton();
        }
        
        function updateEmergencyButton() {
            const btn = document.getElementById('emergencyBtn');
            if (emergencyActive) {
                btn.textContent = 'Desactivar Alarma';
                btn.className = 'btn danger';
            } else {
                btn.textContent = 'Activar Alarma';
                btn.className = 'btn warning';
            }
        }
        
        function updateSensorStatus(data) {
            if (currentMode === 'security') {
                document.getElementById('pirStatus').textContent = data.pirActive ? 'DETECTANDO' : 'MONITOREANDO';
                document.getElementById('pirStatus').className = 'sensor-status ' + (data.pirActive ? 'sensor-active' : 'sensor-standby');
                
                document.getElementById('ledStatus').textContent = data.ledActive ? 'ENCENDIDO' : 'EN ESPERA';
                document.getElementById('ledStatus').className = 'sensor-status ' + (data.ledActive ? 'sensor-active' : 'sensor-standby');
                
                document.getElementById('buzzerStatus').textContent = data.buzzerActive ? 'SONANDO' : 'EN ESPERA';
                document.getElementById('buzzerStatus').className = 'sensor-status ' + (data.buzzerActive ? 'sensor-active' : 'sensor-standby');
            }
        }
        
        async function updateLog() {
            try {
                const response = await fetch('/api/log');
                const log = await response.text();
                document.getElementById('logContent').textContent = log || 'Sin eventos registrados';
            } catch (error) {
                console.error('Error updating log:', error);
            }
        }
        
        function updateTime() {
            const now = new Date();
            const timeString = now.toLocaleTimeString('es-PE', { 
                hour: '2-digit', 
                minute: '2-digit',
                second: '2-digit'
            });
            const timeElement = document.getElementById('currentTime');
            if (timeElement) {
                timeElement.textContent = timeString;
            }
        }
    </script>
</body>
</html>
)rawliteral";

#endif
