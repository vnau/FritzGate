describe('sensors page', () => {
  it('startup is shown', () => {
    cy.intercept('GET', '/api/status', {});

    cy.visit('http://localhost:5173/');
  });

  it('sensors page is shown', () => {
    cy.fixture('status').then((json) => {
      cy.intercept('GET', '/api/status', json)
    });

    cy.visit('http://localhost:5173/')
  });

  it('heating page is shown', () => {
    cy.fixture('status').then((json) => {
      cy.intercept('GET', '/api/status', json)
    });

    cy.visit('http://localhost:5173/#heating')
  });
})