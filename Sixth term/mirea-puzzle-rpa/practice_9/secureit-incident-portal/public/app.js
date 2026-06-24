const FORM_DELAY_MS = 1000;
const TABLE_DELAY_MS = 1500;
const SUCCESS_MESSAGE_DELAY_MS = 1200;
const MESSAGE_HIDE_DELAY_MS = 2800;

const initialIncidents = [];

const state = {
  incidents: [],
  nextId: 1,
  selectedIncidentId: null,
  severityFilter: 'All',
  titleSearch: '',
  messageTimer: null,
  tableTimer: null
};

const elements = {
  loadingSection: document.getElementById('loading_section'),
  formSection: document.getElementById('form_section'),
  tableSection: document.getElementById('table_section'),

  form: document.getElementById('incident_form'),
  title: document.getElementById('incident_title'),
  reporter: document.getElementById('reporter'),
  system: document.getElementById('system'),
  severity: document.getElementById('severity'),

  reportButton: document.getElementById('btn_report_dynamic'),
  validateButton: document.getElementById('btn_report_static'),

  messageContainer: document.getElementById('message_container'),
  statusMessage: document.getElementById('status_message'),
  closeMessageButton: document.getElementById('btn_close_message'),

  tableBody: document.getElementById('incidents_table_body'),
  tableLoader: document.getElementById('table_loader'),
  noIncidentsMessage: document.getElementById('no_incidents_message'),

  startInvestigationButton: document.getElementById('btn_start_investigation'),
  closeIncidentButton: document.getElementById('btn_close_incident'),

  severityFilter: document.getElementById('filter_severity'),
  titleSearch: document.getElementById('search_title'),

  errors: {
    title: document.getElementById('error_incident_title'),
    reporter: document.getElementById('error_reporter'),
    system: document.getElementById('error_system'),
    severity: document.getElementById('error_severity')
  }
};

function initDynamicIds() {
  const randomId = Math.floor(10000 + Math.random() * 90000);
  elements.reportButton.id = `btn_report_${randomId}`;
}

function isReporterValid(value) {
  return /^[A-Za-zА-Яа-яЁё\s-]+$/.test(value.trim());
}

function validateForm(showErrors = false) {
  const title = elements.title.value.trim();
  const reporter = elements.reporter.value.trim();
  const system = elements.system.value;
  const severity = elements.severity.value;

  const errors = {
    title: '',
    reporter: '',
    system: '',
    severity: ''
  };

  if (!title) {
    errors.title = 'Incident Title is required';
  } else if (title.length < 5) {
    errors.title = 'Incident Title must contain at least 5 characters';
  }

  if (!reporter) {
    errors.reporter = 'Reporter field is required';
  } else if (reporter.length < 3) {
    errors.reporter = 'Reporter field must contain at least 3 characters';
  } else if (!isReporterValid(reporter)) {
    errors.reporter = 'Reporter field must contain only letters';
  }

  if (!system) {
    errors.system = 'Please select a system';
  }

  if (!severity) {
    errors.severity = 'Please select severity';
  }

  const isValid = !errors.title && !errors.reporter && !errors.system && !errors.severity;

  if (showErrors) {
    renderValidation(errors);
  }

  elements.reportButton.disabled = !isValid;
  return { isValid, errors };
}

function renderValidation(errors) {
  setFieldError(elements.title, elements.errors.title, errors.title);
  setFieldError(elements.reporter, elements.errors.reporter, errors.reporter);
  setFieldError(elements.system, elements.errors.system, errors.system);
  setFieldError(elements.severity, elements.errors.severity, errors.severity);
}

function setFieldError(field, errorElement, errorText) {
  errorElement.textContent = errorText;
  field.classList.toggle('invalid', Boolean(errorText));
}

function clearValidation() {
  renderValidation({
    title: '',
    reporter: '',
    system: '',
    severity: ''
  });
}

function showMessage(text, type = 'success') {
  clearTimeout(state.messageTimer);

  elements.statusMessage.textContent = text;
  elements.messageContainer.classList.remove('hidden');
  elements.messageContainer.classList.toggle('error-message', type === 'error');

  state.messageTimer = setTimeout(hideMessage, MESSAGE_HIDE_DELAY_MS);
}

function hideMessage() {
  elements.messageContainer.classList.add('hidden');
}

function getSelectedIncident() {
  return state.incidents.find((incident) => incident.id === state.selectedIncidentId) || null;
}

function updateActionButtons() {
  const selectedIncident = getSelectedIncident();

  if (!selectedIncident) {
    elements.startInvestigationButton.disabled = true;
    elements.closeIncidentButton.disabled = true;
    return;
  }

  elements.startInvestigationButton.disabled = selectedIncident.status !== 'Reported';
  elements.closeIncidentButton.disabled = selectedIncident.status === 'Resolved';
}

function getFilteredIncidents() {
  const searchValue = (state.titleSearch || '').trim().toLowerCase();

  return state.incidents.filter((incident) => {
    const severityMatches =
      state.severityFilter === 'All' || incident.severity === state.severityFilter;

    const titleMatches =
      !searchValue || incident.title.toLowerCase().includes(searchValue);

    return severityMatches && titleMatches;
  });
}

function renderTableWithDelay() {
  clearTimeout(state.tableTimer);

  elements.tableLoader.classList.remove('hidden');
  elements.noIncidentsMessage.classList.add('hidden');

  state.tableTimer = setTimeout(() => {
    renderTable();
    elements.tableLoader.classList.add('hidden');
  }, TABLE_DELAY_MS);
}

function loadInitialData() {
  initialIncidents.forEach((incident) => {
    state.incidents.push({
      id: state.nextId++,
      ...incident,
      status: incident.status || 'Reported'
    });
  });

  renderTable();
}

function renderTable() {
  const filteredIncidents = getFilteredIncidents();

  elements.tableBody.innerHTML = '';

  filteredIncidents.forEach((incident) => {
    const row = document.createElement('tr');
    row.id = `incident_row_${incident.id}`;
    row.className = 'incident-row';
    row.dataset.incidentId = String(incident.id);

    if (incident.id === state.selectedIncidentId) {
      row.classList.add('selected');
    }

    row.innerHTML = `
      <td id="incident_${incident.id}_id">${incident.id}</td>
      <td id="incident_${incident.id}_title">${escapeHtml(incident.title)}</td>
      <td id="incident_${incident.id}_reporter">${escapeHtml(incident.reporter)}</td>
      <td id="incident_${incident.id}_system">${escapeHtml(incident.system)}</td>
      <td id="incident_${incident.id}_severity">${escapeHtml(incident.severity)}</td>
      <td id="incident_${incident.id}_status">
        <span id="incident_${incident.id}_status_badge" class="badge">
          ${escapeHtml(incident.status)}
        </span>
      </td>
    `;

    row.addEventListener('click', () => selectIncident(incident.id));
    elements.tableBody.appendChild(row);
  });

  elements.noIncidentsMessage.classList.toggle('hidden', filteredIncidents.length > 0);
  updateActionButtons();
}

function selectIncident(incidentId) {
  state.selectedIncidentId = incidentId;
  renderTable();
}

function addIncident(data) {
  state.incidents.push({
    id: state.nextId++,
    ...data,
    status: 'Reported'
  });

  renderTableWithDelay();
}

function updateIncidentStatus(incidentId, nextStatus) {
  const incident = state.incidents.find((item) => item.id === incidentId);

  if (!incident) {
    showMessage('No incident selected', 'error');
    return;
  }

  incident.status = nextStatus;
  renderTableWithDelay();
}

function handleStartInvestigation() {
  const incident = getSelectedIncident();

  if (!incident) {
    showMessage('Please select an incident first', 'error');
    return;
  }

  if (incident.status !== 'Reported') {
    showMessage('Only Reported incidents can be moved to Investigating', 'error');
    updateActionButtons();
    return;
  }

  updateIncidentStatus(incident.id, 'Investigating');
  showMessage('Incident status changed to Investigating', 'success');
}

function handleCloseIncident() {
  const incident = getSelectedIncident();

  if (!incident) {
    showMessage('Please select an incident first', 'error');
    return;
  }

  if (incident.status === 'Resolved') {
    showMessage('Resolved incident cannot be closed again', 'error');
    updateActionButtons();
    return;
  }

  updateIncidentStatus(incident.id, 'Resolved');
  showMessage('Incident status changed to Resolved', 'success');
}

function resetForm() {
  elements.form.reset();
  clearValidation();
  validateForm(false);
}

function escapeHtml(value) {
  return String(value)
    .replaceAll('&', '&amp;')
    .replaceAll('<', '&lt;')
    .replaceAll('>', '&gt;')
    .replaceAll('"', '&quot;')
    .replaceAll("'", '&#039;');
}

function handleSubmit(event) {
  event.preventDefault();

  const validation = validateForm(true);

  if (!validation.isValid) {
    const firstError = Object.values(validation.errors).find(Boolean);
    showMessage(firstError || 'Form contains errors', 'error');
    return;
  }

  const data = {
    title: elements.title.value.trim(),
    reporter: elements.reporter.value.trim(),
    system: elements.system.value,
    severity: elements.severity.value
  };

  elements.reportButton.disabled = true;

  setTimeout(() => {
    addIncident(data);
    resetForm();
    showMessage('Incident report has been submitted successfully', 'success');
  }, SUCCESS_MESSAGE_DELAY_MS);
}

function bindEvents() {
  [elements.title, elements.reporter, elements.system, elements.severity].forEach((element) => {
    element.addEventListener('input', () => validateForm(true));
    element.addEventListener('change', () => validateForm(true));
  });

  elements.form.addEventListener('submit', handleSubmit);

  elements.validateButton.addEventListener('click', () => {
    const validation = validateForm(true);
    showMessage(
      validation.isValid ? 'Form is valid' : Object.values(validation.errors).find(Boolean),
      validation.isValid ? 'success' : 'error'
    );
  });

  elements.closeMessageButton.addEventListener('click', hideMessage);

  elements.startInvestigationButton.addEventListener('click', handleStartInvestigation);
  elements.closeIncidentButton.addEventListener('click', handleCloseIncident);

  elements.severityFilter.addEventListener('change', () => {
    state.severityFilter = elements.severityFilter.value;
    renderTableWithDelay();
  });

  elements.titleSearch.addEventListener('input', () => {
    state.titleSearch = elements.titleSearch.value;
    renderTableWithDelay();
  });
}


function startApplication() {
  initDynamicIds();
  bindEvents();
  updateActionButtons();

  setTimeout(() => {
    elements.loadingSection.classList.add('hidden');
    elements.formSection.classList.remove('hidden');

    setTimeout(() => {
      elements.tableSection.classList.remove('hidden');
      loadInitialData();
      elements.tableLoader.classList.add('hidden');
    }, TABLE_DELAY_MS);
  }, FORM_DELAY_MS);
}

startApplication();